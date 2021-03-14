#include <stdio.h>
#include <osbind.h>
#include "model.h"

void delay();

int main() {
	struct Dino player;
	struct Dino *dino = &player;
	struct Ptero pter;
	struct Ptero *ptero = &pter;
	struct Cactus cact;
	struct Cactus *cactus = &cact;
	struct Ground groun;
	struct Ground *ground = &groun;

	int i;

	set_dino_pos(dino, 25, 380);
	set_ptero_pos(pter, 25, 380);
	set_cactus_pos(cact, 25, 380);
	printf("dino %d", dino->x);
	printf("\n");
	printf("dino %d", dino->y);
    printf("\n");
	printf("ptero %d", pter->x);
	printf("\n");
	printf("ptero %d", pter->y);
    printf("\n");
	printf("cactus %d", cact->x);
	printf("\n");
	printf("cactus %d", cact->y);
    printf("\n");

	delay();

	

	for(i = 0; i < 5; i++){
		move_ptero(pter);
		printf("ptero %d", pter->x);
    	printf("\n");
	}

	for(i = 0; i < 5; i++){
		move_cactus(cact);
		printf("cactus %d", cact->x);
    	printf("\n");
	}
	
	dino_jump(dino);

	return 0;
}

void delay(){
while (!Cconis())
{}
Cnecin();
}
