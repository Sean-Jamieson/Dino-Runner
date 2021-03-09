
struct Dino{
    unsigned int x, y;
    int delta_y;  
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
};

struct Counter{
    unsigned int x, y;
};

struct Model{
    struct Dino dino;
    struct Cactus cactus;
    struct Ptero ptero;
    struct Ground ground;
    struct Background background;
    struct Counter counter; 
}
