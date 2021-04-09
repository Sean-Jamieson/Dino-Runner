#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "RENDER.H"
#include "RASTER.H"
#include "FBUFF.H"
#include "IMAGES.H"
#include "SOUND.H"
#include "SONG.H"
#include "GET_TIME.H"

struct Model model;

int main()
{

	long time;
	long prev_time;
	long time_passed;

	start_music();
	prev_time = get_time();

	init_model(&model);
	fb_init();
	Vsync();

	fill_screen(fb_get_buff(), 0L);
	fb_flip();
	Vsync();
	fill_screen(fb_get_buff(), 0L);
	generate_obstacle(&model);

	while (model.dino.colliding == false)
	{
		render_game(fb_get_buff(), &model);
		fb_flip();
		Vsync();

		update_dino(&model.dino, &model);
		update_ground(&model.ground);
		update_obstacle(&model.obstacles[0], &model);

		time = get_time();
		time_passed = time - prev_time;
		if (time_passed >= 1)
		{
				if (update_music(time_passed) == 1)
					prev_time = get_time();
		}
		/*update_obstacle(&model.obstacles[1], &model);*/
	}

	/*draw_bmp(Physbase(), cactus_image, -CACTUS_IMG_WIDTH, 300 - CACTUS_IMG_HEIGHT, CACTUS_IMG_WIDTH, CACTUS_IMG_HEIGHT);
	Cconin();*/
	stop_sound();
	fb_exit();
	Vsync();

	return 0;
}
