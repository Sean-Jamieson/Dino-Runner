#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "RENDER.H"
#include "RASTER.H"
#include "FBUFF.H"

int main() {
	unsigned long* base;
	unsigned int i;

	struct Model model;
	struct Dino dino;
	struct Ground ground;

	model.dino = &dino;
	model.ground = &ground;

	fb_init();

	fill_screen(Physbase(), 0L);
	fb_flip();
	fill_screen(fb_get_buff(), 0L);

	dino.x = 0;
	dino.y = 0;
	
	ground.y = 300;
	ground.scroll_offset = 0;

	for (i = 0; i < 640; i++) {
		ground.scroll_offset = i;
		render_game(fb_get_buff(), &model);
		Vsync();
		fb_flip();
	}

	/*fill_screen(fb_get_buff(), 0xFFFFFFFFL);
	clear_area(fb_get_buff(), 0, 0, 640, 20);
	fb_flip();*/

	while (!Cconis());

	fb_exit();

	return 0;
}