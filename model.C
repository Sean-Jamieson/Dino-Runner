#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "IMAGES.H"
#include "RASTER.H"

int obstacle_index = 0;

/* New behavior functions */
void update_dino(struct Dino *dino, struct Model *model) {
	struct Obstacle *obstacle;
	char i;

	dino->prev_x2 = dino->prev_x1;			/* Save previous position */
	dino->prev_y2 = dino->prev_y1;

	dino->prev_x1 = dino->x;
	dino->prev_y1 = dino->y;

	dino->y_velocity += DINO_ACCELERATION;	/* Apply acceleration */
	dino->phys_y += dino->y_velocity;		/* Apply velocity */

	if (dino->phys_y > DINO_GROUND_HEIGHT) {	/* Check ground collision*/
		dino->phys_y = DINO_GROUND_HEIGHT;
		dino->y_velocity = 0.0;
		dino->touching_ground = true;
	}

	jump_dino(dino);

	dino->y = (int)(dino->phys_y);			/* Align visual position with physical position */

	for (i = 0; i < 2; i++) {				/* Check obstacle collision */
		obstacle = &(model->obstacles[i]);

		if (dino->x + 16 < obstacle->x + obstacle->width  &&		/* Check bounding box overlap */
			dino->x  - 16 + dino->width  > obstacle->x &&
			dino->y - dino->height  < obstacle->y &&
			dino->y > obstacle->y - obstacle->height) {
			dino->colliding = true;							/* Enable collision flag */
		}
	}

	if (dino->animation_tick++ >= ANIMATION_TICKS) {
		dino->animation_tick = 0;
		dino->animation_frame++;
		if (dino->animation_frame >= 4)
			dino->animation_frame = 0;
	}

}

/* Make a module that checks for input like we did in class, and have that module call this function instead
   of checking for input in this function */

void jump_dino(struct Dino *dino) {
	if (dino->touching_ground == true) {							/* Check if touchiung ground before jumping */
		if (Cconis()) {												/* is there user input read to be read? */
			char ch = (char)Cnecin();
			if (ch == 'w') {
				dino->touching_ground = false;		   				/* Set touching ground flag to false */
				dino->y_velocity = DINO_JUMP_VELOCITY; 				/* Set the velocity to go upwards */
			}
		}
	}
}

void update_obstacle(struct Obstacle *obstacle, struct Model *model) {
	obstacle->prev_x2 = obstacle->prev_x1;
	obstacle->prev_x1 = obstacle->x;
	obstacle->x -= SCROLL_SPEED;
	
	if (obstacle->animation_frame != 2 && obstacle->animation_tick++ > ANIMATION_TICKS) {				/* what does this do?*/ /* if the obstacle is a ptero and there have been enough animation ticks change the animation frame */
		obstacle->animation_tick = 0;
		obstacle->animation_frame++;
		if (obstacle->animation_frame >= 2)
			obstacle->animation_frame = 0;
	}

	if (obstacle->x < -((signed int)(obstacle->width)))
		generate_obstacle(model);
}

void update_ptero(struct Ptero *ptero) {
	ptero->prev_x2 = ptero->prev_x1;
	ptero->prev_x1 = ptero->x;
	ptero->x -= SCROLL_SPEED;
}

void update_cactus(struct Cactus *cactus) {
	cactus->prev_x2 = cactus->prev_x1;
	cactus->prev_x1 = cactus->x;
	cactus->x -= SCROLL_SPEED;
}

void update_ground(struct Ground *ground) {
	ground->scroll_offset -= SCROLL_SPEED;
	if (ground->scroll_offset < 0)
		ground->scroll_offset += GROUND_IMG_WIDTH;
}

void update_counter(struct Counter *counter) {
	counter->score++;
}

void generate_obstacle(struct Model *model) {
	model->obstacles[obstacle_index].x = NUM_OF_COLUMNS;
	model->obstacles[obstacle_index].y = GROUND_HEIGHT;
	model->obstacles[obstacle_index].prev_x1 = NUM_OF_COLUMNS;
	model->obstacles[obstacle_index].prev_y1 = GROUND_HEIGHT;
	model->obstacles[obstacle_index].prev_x2 = NUM_OF_COLUMNS;
	model->obstacles[obstacle_index].prev_y2 = GROUND_HEIGHT;
	model->obstacles[obstacle_index].width = CACTUS_IMG_WIDTH;
	model->obstacles[obstacle_index].height = CACTUS_IMG_HEIGHT;
	model->obstacles[obstacle_index].animation_frame = CACTUS_SELECT;
	model->obstacles[obstacle_index].animation_tick = 0;

	obstacle_index = obstacle_index == 0 ? 1 : 0;
}

void init_model(struct Model *model) {
	int i;

	model->dino.x = 50;  					/* why is this number significant?*/ /* This is the x position of the dino, now that I think of it the prev_x properties are useless since it only moves up */
	model->dino.y = GROUND_HEIGHT;
	model->dino.prev_x1 = 50;
	model->dino.prev_y1 = GROUND_HEIGHT;
	model->dino.prev_x2 = 50;
	model->dino.prev_y2 = GROUND_HEIGHT;
	model->dino.width = DINO_IMG_WIDTH;
	model->dino.height = DINO_IMG_HEIGHT;
	model->dino.phys_y = 300.0;				/* DINO_PHYS_POS?*/ /* This is the physical height of the ground, the visual position of the ground is slightly higher because of the bumps and such in the image */
	model->dino.y_velocity = 0.0;
	model->dino.colliding = false;
	model->dino.touching_ground = false;
	model->dino.animation_frame = 0;		/* INITIALIZE? */
	model->dino.animation_tick = 0;

	model->ground.y = 290;
	model->ground.scroll_offset = 0;

	for (i = 0; i < 2; i++) {
		model->obstacles[i].x = -200;
		model->obstacles[i].y = GROUND_HEIGHT;
		model->obstacles[i].prev_x1 = -100;
		model->obstacles[i].prev_y1 = GROUND_HEIGHT;
		model->obstacles[i].prev_x2 = -100;
		model->obstacles[i].prev_y2 = GROUND_HEIGHT;
		model->obstacles[i].width = 0;
		model->obstacles[i].height = 0;
		model->obstacles[i].animation_frame = 0;
		model->obstacles[i].animation_tick = 0;
	}
}

/* Old behavior functions */
/*void set_dino_pos(struct Dino *dino, unsigned int x, unsigned int y){                                                              
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
}*/

