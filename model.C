#include "model.h"
#include <stdio.h>

void set_dino_pos(struct Dino *dino, unsigned int x, unsigned int y){                                                              
    dino->x = x;                                    
    dino->y = y;  
}

void move_dino(struct Dino *dino){
    int y;
    dino->delta_y = 2;
    dino->y += dino->delta_y*dino->direction;
    y = dino->y;
    printf("dino %d", y);
    printf("\n");
}
void dino_jump(struct Dino *dino){
    int i;
    dino->direction = -1;
    for (i = 0;i < 5;i++){
          move_dino(dino);
    }
    dino->direction = 1;
    for (i = 0;i < 5;i++){
         move_dino(dino);
    }
}
void set_ptero_pos(struct Ptero *ptero, unsigned int x, unsigned int y){
    ptero->x = x;
    ptero->y = y;
}

void move_ptero(struct Ptero *ptero){
    ptero->delta_x = 2;
    ptero->x -= ptero->delta_x;
}

void set_cactus_pos(struct Cactus *cactus, unsigned int x, unsigned int y){
    cactus->x = x;
    cactus->y = y;
}
void move_cactus(struct Cactus *cactus){
    cactus->delta_x = 2;
    cactus->x -= cactus->delta_x;
}

void set_ground_pos(struct Ground *ground, unsigned int x, unsigned int y){
    ground->x = x;
    ground->y = y;
}
void move_ground(struct Ground *ground){
    ground->delta_x = 2;
    ground->x -= ground->delta_x;
}

void set_background_pos(struct Background *background, unsigned int x, unsigned int y){
    background->x = x;
    background->y = y;
}

void move_background(struct Background *background){
    background->delta_x = 1;
    background->x -= background->delta_x;
}

