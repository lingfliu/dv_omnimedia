#clk_close()
#{
#
#}

clk_cfg()
{
	#himm 0x2003002C 0xFFFF0000;		#3531 VICAPʱ���ſء���λ����λ
	#himm 0x20030030 0x002AAAA0;		#3531 VICAPʱ��Դ������ʱ���ſء�divʱ��ѡ��
	#himm 0x20030034 0x7fe13fd0;		#3531 VOUʱ��ȫ��
	#himm 0x20030038 0x00010000;		#3531 VOU������λ
	#himm 0x2003003c 0x0000004c;		#3531 HDMIʱ��/������λ
	#himm 0x20030040 0x2;	#3531 VEDU0������λ
	#himm 0x20030044 0x2;	#3531 VEDU1������λ
	#himm 0x20030048 0x2;	#3531 VPSS0������λ
	#himm 0x2003004c 0x2;	#3531 VPSS1������λ
	himm 0x20030050 0x2;	#3531 VDH0������λ
	himm 0x20030054 0x2;	#3531 VDH1������λ
	#himm 0x20030058 0x2;	#3531 TDE������λ
	#himm 0x20030060 0x2;	#3531 JPGE������λ
	himm 0x20030064 0x2;	#3531 JPGD������λ
	#himm 0x20030068 0x2;	#3531 MDU������λ
	#himm 0x20030074 0x2;	#3531 VCMP������λ
	himm 0x200300E0 0x2;	#3531 DMA������λ
	#himm 0x2003006C 0x2;	#3531 IVE������λ
}


#clk_close
clk_cfg
#clk_cfg_hi3531fpga
