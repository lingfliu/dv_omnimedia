/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : region_ext.h
  �� �� ��   : ����
  ��    ��   : l64467
  ��������   : 2010��12��18��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��12��18��
    ��    ��   : l64467
    �޸�����   : �����ļ�
  
******************************************************************************/
#ifndef __REGION_EXT_H__
#define __REGION_EXT_H__

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_region.h"

#ifdef __cplusplus
    #if __cplusplus
    extern "C"{
    #endif
#endif /* End of #ifdef __cplusplus */



typedef struct hiRGN_COMM_S
{
    HI_BOOL bShow;           /* �����Ƿ���ʾ*/
    POINT_S stPoint;         /*������ʼλ��*/
    SIZE_S  stSize;          /*������ʼ���*/
    HI_U32  u32Layer;        /*������*/
    HI_U32  u32BgColor;      /*���򱳾�ɫ*/
    HI_U32  u32GlobalAlpha;  /*����ȫ��ALPHA*/
    HI_U32  u32FgAlpha;      /*����ǰ��ALPHA*/
    HI_U32  u32BgAlpha;      /*���򱳾�ALPHA*/
    HI_U32  u32PhyAddr;      /*������ռ���ڴ�������ַ*/
	HI_U32  u32VirtAddr;     /*����ռ���ڴ�������ַ*/
	HI_U32  u32Stride;       /*���������ݵ� Stride*/
    PIXEL_FORMAT_E      enPixelFmt;     /*�������ظ�ʽ*/
    RGN_ATTACH_FIELD_E  enAttachField;  /* �����ŵ�֡����Ϣ */

    OVERLAY_QP_INFO_S stQpInfo; /*QP��Ϣ*/
    
    OVERLAY_INVERT_COLOR_S stInvColInfo; /*��ɫ��Ϣ*/
    
}RGN_COMM_S;

typedef struct hiRGN_INFO_S
{
    HI_U32 u32Num;           /* �������*/
    HI_BOOL bModify;         /*�Ƿ��Ѿ��޸�*/
    RGN_COMM_S **ppstRgnComm;/* ���򹫹���Ϣָ������ĵ�ַ*/ 
}RGN_INFO_S;


typedef struct hiRGN_REGISTER_INFO_S
{
    MOD_ID_E    enModId;
    HI_U32      u32MaxDevCnt;   /* If no dev id, should set it 1 */
    HI_U32      u32MaxChnCnt;
} RGN_REGISTER_INFO_S;


typedef struct hiRGN_EXPORT_FUNC_S
{
    HI_S32 (*pfnRgnRegisterMod)(RGN_TYPE_E enType,const RGN_REGISTER_INFO_S *pstRgtInfo);
    HI_S32 (*pfnUnRgnRegisterMod)(RGN_TYPE_E enType,MOD_ID_E enModId);
    
    HI_S32 (*pfnRgnGetRegion)(RGN_TYPE_E enType, const MPP_CHN_S *pstChn, RGN_INFO_S *pstRgnInfo);
    HI_S32 (*pfnRgnPutRegion)(RGN_TYPE_E enType, const MPP_CHN_S *pstChn);
    HI_S32 (*pfnRgnSetModifyFalse)(RGN_TYPE_E enType, const MPP_CHN_S *pstChn);
}RGN_EXPORT_FUNC_S;


#define CKFN_RGN() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN))


#define CKFN_RGN_RegisterMod() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnRegisterMod)
    

#define CALL_RGN_RegisterMod(enType,pstRgtInfo) \
    FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnRegisterMod(enType,pstRgtInfo)


#define CKFN_RGN_UnRegisterMod() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnUnRgnRegisterMod)
    

#define CALL_RGN_UnRegisterMod(enType,enModId) \
    FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnUnRgnRegisterMod(enType,enModId)
    

#define CKFN_RGN_GetRegion() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnGetRegion)
    

#define CALL_RGN_GetRegion(enType,pstChn,pstRgnInfo) \
    FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnGetRegion(enType,pstChn,pstRgnInfo)
    


#define CKFN_RGN_PutRegion() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnPutRegion)
    
#define CALL_RGN_PutRegion(enType,pstChn) \
    FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnPutRegion(enType,pstChn)


#define CKFN_RGN_SetModifyFalse() \
    (NULL != FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnSetModifyFalse)
    
#define CALL_RGN_SetModifyFalse(enType,pstChn) \
    FUNC_ENTRY(RGN_EXPORT_FUNC_S, HI_ID_RGN)->pfnRgnSetModifyFalse(enType,pstChn)


#ifdef __cplusplus
    #if __cplusplus
    }
    #endif
#endif /* End of #ifdef __cplusplus */

#endif /* __REGION_EXT_H__ */



