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

	clear_splash(Physbase());
	render_start(Physbase());

	while(!Cconis()){
		time = get_time();
		time_passed = time - prev_time;
		if (time_passed >= 1)
		{
				if (update_music(time_passed) == 1)
					prev_time = get_time();
		}
	}
	clear_splash(Physbase());
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
	}
	stop_sound();
	dead_sound();
	time_passed = 0;
	while(time_passed < 25)
	{
	time = get_time();
	time_passed = time - prev_time;
	}
		

	stop_sound();
	clear_splash(Physbase());
	render_end(Physbase());
	while(!Cconis())
		;

	fb_exit();
	Vsync();

	return 0;
}
