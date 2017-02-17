== Linux kernel configuration
1. Enable ethernet dhcp
2. Enable gdbserver for development

== SDK installation and system compiling
- Install toolchain before compile
1. kernel/linux.3.0.y/kernel/timeconst.pl, remove "defined" in if(!defined(@val))
2. u-boot/tools/ copy mkimage to /usr/bin
3. rm pub/bin/board_ulibc/pci and pub/ rootfs
4. busybox/Makefile, line 437 remove config, line 1288, remove /%/prepare

N.B.: The mpp provided are build under glibc, use CROSS_COMPILE=arm-hisiv200-linux- for all compilation

== Uboot and bootargs+bootcmd
Suppose we have 16 M spi flash and >256 M nand flash, system compiled under glibc.

Preparation: 
1. Connect hi3531 and pc to the same ethernet. 
2. Connect the serial
3. Use makeyaffs to conver nand yaffs2 system file (rootfs.yaffs2 e.g.) to match the nand flash's pagesize and ecctype (you may check it when the board loads the system)

Procedures:
1. Burn uboot by fastboot via serial
2. Start the board, enter uboot
3. Start tftp on PC
4. mw.b 82000000 ff SIZE_NEEDED
5. Download the uImage to 82000000
6. Erase the flash
7. Write uImage to the flash
8. Same procedure to the rootfs
9. set bootargs 'mem=64M, ......'
10. set bootcmd 'spi probe 0; spi read ...; nand read...;'
11. sa and reset

== MPP ko loading
1. Modify the mmz.ko loading: all mmz memory allocation should start with offset greater than the OS memory. E.g. if mem=64 M for uboot bootargs then mmz should start from 84000000.
2. Be sure all mmz memory are not overlapped.
3. Start load3531 in background.
4. Unload uncessary modules

== /dev/
adec: 
aenc: 
ai: 
ao: 
hdmi: 
hi_tde: hisi tde
ive: intelligent video engine
jpeg:
mice: mouse devices
mmz_userdev: media memory zone
rgn: region for media
usbdev1.1:
usbdev1.2:
vdec: 
venc: 
vga_arbiter: vga out
vi: 
vo:
vpss: video process system
