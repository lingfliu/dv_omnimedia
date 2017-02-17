#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "mpi_sys.h"
#include "hi_comm_vb.h"
#include "mpi_vb.h"
#include "hi_comm_vi.h"
#include "mpi_vi.h"

#define MAX_FRM_CNT 256

/* sp420 ת��Ϊ p420 ; sp422 ת��Ϊ p422  */
void sample_yuv_dump(VIDEO_FRAME_S * pVBuf, FILE *pfd)
{
    unsigned int w, h;
    char * pVBufVirt_Y;
    char * pVBufVirt_C;
    char * pMemContent;
    unsigned char TmpBuff[2000];                //������ֵ̫С��ͼ��ܴ�Ļ��治��
    HI_U32 phy_addr,size;
	HI_CHAR *pUserPageAddr[2];
    PIXEL_FORMAT_E  enPixelFormat = pVBuf->enPixelFormat;
    HI_U32 u32UvHeight;/* ��Ϊplanar ��ʽʱ��UV�����ĸ߶� */
    
    if (PIXEL_FORMAT_YUV_SEMIPLANAR_420 == enPixelFormat)
    {
        size = (pVBuf->u32Stride[0])*(pVBuf->u32Height)*3/2;    
        u32UvHeight = pVBuf->u32Height/2;
    }
    else
    {
        size = (pVBuf->u32Stride[0])*(pVBuf->u32Height)*2;   
        u32UvHeight = pVBuf->u32Height;
    }

    phy_addr = pVBuf->u32PhyAddr[0];

    //printf("phy_addr:%x, size:%d\n", phy_addr, size);
    pUserPageAddr[0] = (HI_CHAR *) HI_MPI_SYS_Mmap(phy_addr, size);	
    if (NULL == pUserPageAddr[0])
    {
        return;
    }
    //printf("stride: %d,%d\n",pVBuf->u32Stride[0],pVBuf->u32Stride[1] );
    
	pVBufVirt_Y = pUserPageAddr[0]; 
	pVBufVirt_C = pVBufVirt_Y + (pVBuf->u32Stride[0])*(pVBuf->u32Height);

    /* save Y ----------------------------------------------------------------*/
    fprintf(stderr, "saving......Y......");
    fflush(stderr);
    for(h=0; h<pVBuf->u32Height; h++)
    {
        pMemContent = pVBufVirt_Y + h*pVBuf->u32Stride[0];
        fwrite(pMemContent, pVBuf->u32Width, 1, pfd);
    }
    fflush(pfd);
    

    /* save U ----------------------------------------------------------------*/
    fprintf(stderr, "U......");
    fflush(stderr);
    for(h=0; h<u32UvHeight; h++)
    {
        pMemContent = pVBufVirt_C + h*pVBuf->u32Stride[1];

        pMemContent += 1;

        for(w=0; w<pVBuf->u32Width/2; w++)
        {
            TmpBuff[w] = *pMemContent;
            pMemContent += 2;
        }
        fwrite(TmpBuff, pVBuf->u32Width/2, 1, pfd);
    }
    fflush(pfd);

    /* save V ----------------------------------------------------------------*/
    fprintf(stderr, "V......");
    fflush(stderr);
    for(h=0; h<u32UvHeight; h++)    
    {
        pMemContent = pVBufVirt_C + h*pVBuf->u32Stride[1];

        for(w=0; w<pVBuf->u32Width/2; w++)
        {
            TmpBuff[w] = *pMemContent;
            pMemContent += 2;
        }
        fwrite(TmpBuff, pVBuf->u32Width/2, 1, pfd);
    }
    fflush(pfd);
    
    fprintf(stderr, "done %d!\n", pVBuf->u32TimeRef);
    fflush(stderr);
    
    HI_MPI_SYS_Munmap(pUserPageAddr[0], size);    
}

HI_S32 SAMPLE_MISC_ViDump(VI_CHN ViChn, HI_U32 u32Cnt)
{	
    HI_S32 i, s32Ret;
    VIDEO_FRAME_INFO_S stFrame;
    //VIDEO_FRAME_INFO_S astFrame[MAX_FRM_CNT];
    HI_CHAR szYuvName[128];
    HI_CHAR szPixFrm[10];
    FILE *pfd;  
    
    printf("\nNOTICE: This tool only can be used for TESTING !!!\n");
    printf("usage: ./vi_dump [vichn] [frmcnt]. sample: ./vi_dump 0 5\n\n");

    if (HI_MPI_VI_SetFrameDepth(ViChn, 1))
    {        
        printf("HI_MPI_VI_SetFrameDepth err, vi chn %d \n", ViChn);
        return -1;
    }

    usleep(5000);
    
    if (HI_MPI_VI_GetFrame(ViChn, &stFrame))
    {        
        printf("HI_MPI_VI_GetFrame err, vi chn %d \n", ViChn);
        return -1;
    } 
    
    /* make file name */
    strcpy(szPixFrm, 
    (PIXEL_FORMAT_YUV_SEMIPLANAR_420 == stFrame.stVFrame.enPixelFormat)?"p420":"p422");    
    sprintf(szYuvName, "./vi chn %d_%d_%d_%s_%d.yuv", ViChn,
        stFrame.stVFrame.u32Width, stFrame.stVFrame.u32Height,szPixFrm,u32Cnt);        
	printf("Dump YUV frame of vi chn %d  to file: \"%s\"\n", ViChn, szYuvName);

    HI_MPI_VI_ReleaseFrame(ViChn, &stFrame);
    
    /* open file */
    pfd = fopen(szYuvName, "wb");
    
    if (NULL == pfd)
    {
        return -1;
    }
    
    /* get VI frame  */    
    for (i=0; i<u32Cnt; i++)
    {
        s32Ret = HI_MPI_VI_GetFrame(ViChn, &stFrame);
        if (HI_SUCCESS != s32Ret)
        {        
            printf("get vi chn %d frame err\n", ViChn);
            printf("only get %d frame\n", i);
            break;
        }

        /* save VI frame to file */
		sample_yuv_dump(&stFrame.stVFrame, pfd);
        
        /* release frame after using */
        s32Ret = HI_MPI_VI_ReleaseFrame(ViChn, &stFrame);
        if (HI_SUCCESS != s32Ret)
        {
            printf("Release vi chn %d frame err\n", ViChn);
            printf("only get %d frame\n", i);
            break;
        }
#if 0        
        if (astFrame[i].stVFrame.u32Width != stFrame.stVFrame.u32Width
            || astFrame[i].stVFrame.u32Height != stFrame.stVFrame.u32Height)
        {
            printf("vi size has changed when frame %d, break\n",i);
            break;
        }
#endif
    }

    fclose(pfd);
    
	return 0;
}

HI_S32 main(int argc, char *argv[])
{	 
    VI_CHN ViChn = 0;
    HI_U32 u32FrmCnt = 1;

    if (argc > 1)/* VIͨ����*/
    {
        ViChn = atoi(argv[1]);
    }
    
    if (argc > 2)
    {
        u32FrmCnt = atoi(argv[2]);/* ��Ҫ�ɼ���֡��Ŀ*/
    } 
    
    SAMPLE_MISC_ViDump(ViChn, u32FrmCnt);

	return HI_SUCCESS;
}



