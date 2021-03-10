#include "MODEL.H"
#include "BEHAVIOUR.H"

void set_dino_pos(struct Dino *dino, x, y){
    dino->x = x;
    dino->y = y;
}

void move_dino(struct Dino *dino){
    dino->y += dino->delta_y*dino->direction;
}



void set_ptero_pos(struct Ptero *ptero, x, y){
    ptero->x = x;
    ptero->y = y;
}

void move_ptero(struct Ptero *ptero){
    ptero->x += ptero->delta_x;
}

void set_cactus_pos(struct Cactus cactus, x, y){
    cactus->x = x;
    cactus->y = y;
}
void move_cactus(struct Cactus *cactus){
    cactus->x += cactus->delta_x;
}

void move_ground(struct Ground *ground){
    ground->x += ground->delta_x;
}

void move_background(struct Background *background){
    background->x += background->delta_x;
}

