
clk_cfg_hi3531fpga()
{
	#himm 0x20030044 0x2;	#3532IVE������λ
	#himm 0x2003006c 0x2;	#3531IVE������λ
	himm 0x20030040 0x0;	#3531 VEDU0������λ
	himm 0x20030060 0x0;	#3531 JPGE������λ
	himm 0x20030068 0x0;	#3531 MDU������λ
	himm 0x20030074 0x0;	#3531 VCMP������λ
	himm 0x20030058 0x0;	#3531 TDE������λ
	himm 0x20030048 0x0;	#3531 VPSS0������λ
	himm 0x20030050 0x0;	#3531 VDH0������λ
	himm 0x20030064 0x0;	#3531 JPGD0������λ
#	himm 0x2003002c 0xf000; #3531 VICAP��BT1120�˿�ʱ�ӷ���

	himm 0x20030038 0x00040010  #VDP BT1120ʱ�ӷ���
	himm 0x20030034 0xC0;   #VDPʱ�ӷ���
}


clk_cfg_hi3531fpga
