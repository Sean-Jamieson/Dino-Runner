#include <stdio.h>
#include <osbind.h>
#include "RASTER.H"
#include "TESTIMG.H"
#include "FBUFF.H"

int main() {
	unsigned long *base;
	unsigned int i;

/*	fb_init();
	base = fb_get_buff();

	fill_screen(base, 0x00);
	fb_flip();
	base = fb_get_buff();
	fill_screen(base, 0x00); */

	base = Physbase();
	fill_screen(base, 0L);

	draw_bmp((char*)base, img, 10, 390, 640, 20);

	getchar();

/*	for (i = 0; i < 640; i++) {
		base = fb_get_buff();
		clear_area(base, 0, 200, 640, 20);
		draw_bmp((char*) base, img, 0, 30, 640, 20);
		draw_bmp((char*) base, img, -12, 70, 640, 20);
		clear_area(base, 0, 110, 640, 20);
		draw_ground((char*) base, img, 110, 640, 20, i);
		fb_flip();
	}*/

/*	fb_exit(); */

	return 0;
}