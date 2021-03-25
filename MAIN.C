#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "RENDER.H"
#include "RASTER.H"
#include "FBUFF.H"
#include "IMAGES.H"

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
		if (Cconis()) {												
			char ch = (char)Cnecin();
			if (ch == 'q') { 
				fb_exit();
				return 0 ;
			}
		}
		/*update_obstacle(&model.obstacles[1], &model);*/
	}

	/*draw_bmp(Physbase(), cactus_image, -CACTUS_IMG_WIDTH, 300 - CACTUS_IMG_HEIGHT, CACTUS_IMG_WIDTH, CACTUS_IMG_HEIGHT);
	Cconin();*/

	fb_exit();

	return 0;
}

