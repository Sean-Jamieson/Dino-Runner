#include "model.h"
#include <stdio.h>

void set_dino_pos(struct Dino *dino, int x, int y){         //needs some love. address error?
    dino->x = x;                                    
    dino->y = y;  
}

void move_dino(struct Dino *dino){
    int y;
    dino->delta_y = 2;
    dino->y += dino->delta_y*dino->direction;
    y = dino->y;
    printf("%d", y);
    printf("\n");
}
void dino_jump(struct Dino *dino){
    int i;
    dino->direction = -1;
    for (i = 0;i < 80;i++){
          move_dino(dino);
    }
    dino->direction = 1;
    for (i = 0;i < 80;i++){
         move_dino(dino);
    }
}
void set_ptero_pos(struct Ptero *ptero, int x, int y){
    ptero->x = x;
    ptero->y = y;
}

void move_ptero(struct Ptero *ptero){
    ptero->delta_x = 2;
    ptero->x -= ptero->delta_x;
}

void set_cactus_pos(struct Cactus *cactus, int x, int y){
    cactus->x = x;
    cactus->y = y;
}
void move_cactus(struct Cactus *cactus){
    cactus->delta_x = 2;
    cactus->x -= cactus->delta_x;
}

void move_ground(struct Ground *ground){
    ground->delta_x = 2;
    ground->x -= ground->delta_x;
}

void move_background(struct Background *background){
    background->delta_x = 1;
    background->x -= background->delta_x;
}

