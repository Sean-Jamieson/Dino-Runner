#include <stdio.h>
#include "RASTER.H"
#include "MODEL.H"
#include "RENDER.H"
#include "IMAGES.H"

void render_game(unsigned long *base, struct Model *model) {
	clear_dino(base, model);
	clear_ground(base, model);
	clear_obstacles(base, model);

	render_dino(base, model);
	render_ground(base, model);
	render_obstacles(base, model);
	/*draw_bmp(base, cactus_image, -100, 300, CACTUS_IMG_WIDTH, CACTUS_IMG_HEIGHT);*/
}

void render_dino(unsigned long *base, struct Model *model) {
	unsigned long *dino_img = dino_images[model->dino.animation_frame];
	draw_bmp(base, dino_img, model->dino.x, model->dino.y - DINO_IMG_HEIGHT, DINO_IMG_WIDTH, DINO_IMG_HEIGHT);
}

void clear_dino(unsigned long *base, struct Model *model) {
	clear_area(base, model->dino.prev_x2, model->dino.prev_y2 - DINO_IMG_HEIGHT, DINO_IMG_WIDTH, DINO_IMG_HEIGHT);
}

void render_ground(unsigned long *base, struct Model *model) {
	draw_ground(base, ground_img, model->ground.y, GROUND_IMG_WIDTH, GROUND_IMG_HEIGHT, model->ground.scroll_offset);
}

void clear_ground(unsigned long *base, struct Model *model) {
	clear_area(base, 0, model->ground.y, GROUND_IMG_WIDTH, GROUND_IMG_HEIGHT);
}

void render_obstacles(unsigned long *base, struct Model *model) {
	int i;
	unsigned int frame = model->obstacles[i].animation_frame;
	for (i = 0; i < 1; i++) {
		if (frame = 2) {			/* if the obstacle is a cactus */
			printf("%d\n", model->obstacles[i].x);
			draw_bmp(base, cactus_image, model->obstacles[i].x, model->obstacles[i].y - CACTUS_IMG_HEIGHT, CACTUS_IMG_WIDTH, CACTUS_IMG_HEIGHT);
		} else {					/* if the obstacle is a pterodactyl */
			draw_bmp(base, ptero_images[frame], model->obstacles[i].x, model->obstacles[i].y - PTERO_IMG_HEIGHT, PTERO_IMG_WIDTH, PTERO_IMG_HEIGHT);
		}
	}
}

void clear_obstacles(unsigned long *base, struct Model *model) {
	int i;
	unsigned int frame = model->obstacles[i].animation_frame;
	for (i = 0; i < 2; i++) {
		if (frame == 2)
			clear_area(base, model->obstacles[i].x, model->obstacles[i].y - CACTUS_IMG_HEIGHT, CACTUS_IMG_WIDTH, CACTUS_IMG_HEIGHT);
		else
			clear_area(base, model->obstacles[i].x, model->obstacles[i].y - PTERO_IMG_HEIGHT, PTERO_IMG_WIDTH, PTERO_IMG_HEIGHT);
	}
}