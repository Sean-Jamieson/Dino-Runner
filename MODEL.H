#include "BOOLEAN.H"

#define SCROLL_SPEED 15

#define DINO_ACCELERATION 	5.0
#define DINO_JUMP_VELOCITY 	-40.0
#define DINO_HEIGHT 		128.0
#define DINO_GROUND_HEIGHT 	300
#define GROUND_HEIGHT       300
#define CACTUS_SELECT       2
#define PTERO_SELECT		0
#define OBSTACLE_START_POS 	-100
#define ANIMATION_TICKS		2
#define COLLIDER_OFFSET		16

struct Dino {
	signed int x, y;
	signed int prev_x1, prev_y1;
	signed int prev_x2, prev_y2;
	unsigned int width, height;
	float phys_y;
	float y_velocity;
	bool colliding;
	bool touching_ground;
	unsigned int animation_tick;
	unsigned int animation_frame;
};

struct Obstacle {
	signed int x, y;
	signed int prev_x1, prev_y1;
	signed int prev_x2, prev_y2;
	unsigned int width, height;
	unsigned int animation_frame;
	unsigned int animation_tick;
};

struct Ptero {
	signed int x, y;
	signed int prev_x1, prev_y1;
	signed int prev_x2, prev_y2;
	unsigned int animation_frame;
};

struct Cactus {
	signed int x, y;
	signed int prev_x1, prev_y1;
	signed int prev_x2, prev_y2;
};

struct Ground {
	signed int y;
	signed int scroll_offset;
};

struct Background {
	unsigned int scroll_offset;
};

struct Counter {
	signed int x, y;
	unsigned int score;
};

struct Model {
	struct Dino dino;
	struct Obstacle obstacles[2];
	struct Ground ground;
	struct Background background;
	struct Counter counter;
};

/* New behavior functions */
void update_dino(struct Dino *dino, struct Model *model);
void jump_dino(struct Dino *dino);

void update_obstacle(struct Obstacle *obstacle, struct Model *model);

void update_ptero(struct Ptero *ptero);

void update_cactus(struct Cactus *cactus);

void update_ground(struct Ground *ground);

void update_counter(struct Counter *counter);

void generate_obstacle(struct Model *model);

void init_model(struct Model *model);

/* Old behavior functions */
/*void set_dino_pos(struct Dino *dino, unsigned int x, unsigned int y);
void move_dino(struct Dino *dino);
void set_ptero_pos(struct Ptero *ptero, unsigned int x, unsigned int y);
void move_ptero(struct Ptero *ptero);
void set_cactus_pos(struct Cactus *cactus, unsigned int x, unsigned int y);
void move_cactus(struct Cactus *cactus);
void move_ground(struct Ground *ground);
void move_background(struct Background *background);*/
