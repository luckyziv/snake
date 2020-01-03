#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>	/* open() */
#include <linux/fb.h>	/* struct fb_var_screeninfo */
#include <sys/ioctl.h>	/* ioctl() */
#include <sys/mman.h>
#include <fcntl.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "typedef.h"

struct fb_var_screeninfo vinfo;

#define RGB888(r, g, b) ((0xff & r) << 16 | (0xff & g) << 8 | (b & 0xff))
void show(void);
void draw_side(unsigned long* addr);

int main(int argc, char *argv)
{
	system("clear");	/* 清屏函数 */

	/* 屏幕设备操作 */
	/* step1 */
	s32 fd = open("/dev/fb0", O_RDWR);
	if (fd < 0) {
		perror("open err. \r\n");
		exit(EXIT_FAILURE);
	} 	
	
	/* step2 */
	s32 fret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if (fret < 0) {
		perror("ioctl err. \r\n");
		exit(EXIT_FAILURE);
	}
	
	/* step3 */
#if 0
	printf("vinfo.xres: %d\r\n", vinfo.xres);
	printf("vinfo.yres: %d\r\n", vinfo.yres);
	printf("vinfo.bits_per_pixel: %d\r\n", vinfo.bits_per_pixel);
#endif
	
	unsigned long* addr = mmap(NULL, 
					(vinfo.xres*vinfo.yres*vinfo.bits_per_pixel>>3),
					PROT_READ | PROT_WRITE,
					MAP_SHARED,
					fd,
					0);

	draw_side(addr);

	while(1);

	return 0;
}


void show(void)
{
	printf("[%s] running...\r\n", __func__);
}


void draw_side(unsigned long* addr)
{
	int i, j;
	
	for(i = 180; i < 200; i++){
		for(j = 190; j<410; j++)
			*(addr + i*688 + j) = RGB888(0, 0, 0xff);
	}

	for(i = 600; i < 620; i++){
		for(j = 190; j<410; j++)
			*(addr + i*688 + j) = RGB888(0, 0, 0xff);
	}

	for(i = 200; i < 600; i++){
		for(j = 190; j<200; j++)
			*(addr + i*688 + j) = RGB888(0, 0, 0xff);
	}

	for(i = 200; i < 600; i++){
		for(j = 400; j<410; j++)
			*(addr + i*688 + j) = RGB888(0, 0, 0xff);
	}
}


