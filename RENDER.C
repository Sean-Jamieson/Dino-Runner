#include "RASTER.H"
#include "MODEL.H"
#include "RENDER.H"
#include "IMAGES.H"

void render_game(unsigned long *base, struct Model *model) {
	render_dino(base, model);
	render_ground(base, model);
}

void render_dino(unsigned long *base, struct Model *model) {
	clear_area(base, model->dino->x, model->dino->y, DINO_IMG_WIDTH, DINO_IMG_HEIGHT);
	draw_bmp(base, dino_img, model->dino->x, model->dino->y, DINO_IMG_WIDTH, DINO_IMG_HEIGHT);
}

void render_ground(unsigned long *base, struct Model *model) {
	clear_area(base, 0, model->ground->y, GROUND_IMG_WIDTH, GROUND_IMG_HEIGHT);
	draw_ground(base, ground_img, model->ground->y, GROUND_IMG_WIDTH, GROUND_IMG_HEIGHT, model->ground->scroll_offset);
}