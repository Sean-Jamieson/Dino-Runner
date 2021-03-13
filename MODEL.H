
struct Dino{
    unsigned int x, y;
    float delta_y;  
    float direction;
};

struct Ptero{
    unsigned int x, y;
    int delta_x;
};

struct Cactus{
    unsigned int x, y;
    int delta_x;
};

struct Ground{
    unsigned int x, y;
    int delta_x;
};

struct Background{
    unsigned int x, y;
    int delta_x;
};

struct Counter{
    unsigned int x, y;
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
