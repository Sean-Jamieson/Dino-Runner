#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "RENDER.H"
#include "RASTER.H"
#include "FBUFF.H"

struct Model model;

int main() {

	init_model(&model);

	fb_init();

	fill_screen(fb_get_buff(), 0L);
	fb_flip();
	fill_screen(fb_get_buff(), 0L);

	generate_obstacle(&model);

	while (model.dino.colliding == false) {
		render_game(fb_get_buff(), &model);
		Vsync();
		fb_flip();

		update_dino(&model.dino, &model);
		update_ground(&model.ground);
		update_obstacle(&model.obstacles[0], &model);
		/*update_obstacle(&model.obstacles[1], &model);*/
	}

	fb_exit();

	return 0;
}

