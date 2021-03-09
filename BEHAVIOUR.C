#include "MODEL.H"
#include "BEHAVIOUR.H"

move_dino(struct Dino *dino){
    dino->y += dino->delta_y*dino->direction;
}

move_ptero(struct Ptero *ptero){
    ptero->x += ptero->delta_x;
}

move_cactus(struct Cactus *cactus){
    cactus->x += cactus->delta_x;
}

move_ground(struct Ground *ground){
    ground->x += ground->delta_x;
}

move_background(struct Background *background){
    background->x += background->delta_x;
}

