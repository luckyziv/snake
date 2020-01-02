#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>	/* open() */
#include <linux/fb.h>	/* struct fb_var_screeninfo */
#include <sys/ioctl.h>	/* ioctl() */

#include "typedef.h"

struct fb_var_screeninfo vinfo;

void show(void);

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
	printf("vinfo.xres: %d\r\n", vinfo.xres);
	printf("vinfo.yres: %d\r\n", vinfo.yres);
	printf("vinfo.bits_per_pixel: %d\r\n", vinfo.bits_per_pixel);

	return 0;
}


void show(void)
{
	printf("[%s] running...\r\n", __func__);
}
