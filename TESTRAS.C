#include <stdio.h>
#include <osbind.h>
#include "RASTER.H"
#include "TESTIMG.H"
#include "FBUFF.H"

int main() {
	unsigned char *base;
	unsigned int i;

	fb_init();
	base = fb_get_buff();

	fill_screen(base, 0x00);
	fb_flip();
	base = fb_get_buff();
	fill_screen(base, 0x00);

	for (i = 0; i < 640; i++) {
		base = fb_get_buff();
		clear_area(base, 0, 200, 640, 20);
		draw_bmp(base, img, 0, 30, 640, 20);
		draw_bmp(base, img, -8, 50, 640, 20);
		clear_area(base, 0, 70, 640, 20);
		draw_ground(base, img, 70, 640, 20, i);
		fb_flip();
	}

	fb_exit();

	return 0;
}