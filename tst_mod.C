#include <stdio.h>
#include <osbind.h>
#include "model.h"


int main() {
	struct Dino *dino;
	
	struct Ptero *ptero;
	struct Cactus *cactus;

	int i;
	
	dino->x = 25;
	dino->y = 380;
	printf("here");
	
	ptero->x = 25;
	ptero->y = 350;
	/*
	for(i = 0; i > 30; i++){
		move_ptero(ptero);
	}
	*/
	dino_jump(dino);

	return 0;
}