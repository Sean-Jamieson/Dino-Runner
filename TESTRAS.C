#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "RENDER.H"
#include "RASTER.H"

int main() {
	unsigned long* base;
	unsigned int i;

	struct Model model;
	struct Dino dino;
	struct Ground ground;

	base = Physbase();
	fill_screen(base, 0L);

	model.dino = &dino;
	model.ground = &ground;

	dino.x = 50;
	dino.y = 50;
	
	ground.y = 300;
	ground.scroll_offset = 0;

	render_game(base, &model);

	while (!Cconis());

	return 0;
}