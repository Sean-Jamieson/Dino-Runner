
struct Dino{
	signed int x, y;
	float y_velocity;
};

struct Ptero{
	signed int x, y;
	int delta_x;
};

struct Cactus{
	signed int x, y;
	int delta_x;
};

struct Ground{
	int y;
	int scroll_offset;
};

struct Background{
	int x, y;
	int delta_x;
};

struct Counter{
	int x, y;
};

struct Model{
	struct Dino *dino;
	struct Cactus *cactus;
	struct Ptero *ptero;
	struct Ground *ground;
	struct Background *background;
	struct Counter *counter; 
};

void set_dino_pos(struct Dino *dino, int x, int y);
void move_dino(struct Dino *dino);
void set_ptero_pos(struct Ptero *ptero, int x, int y);
void move_ptero(struct Ptero *ptero);
void set_cactus_pos(struct Cactus *cactus, int x, int y);
void move_cactus(struct Cactus *cactus);
void move_ground(struct Ground *ground);
void move_background(struct Background *background);
