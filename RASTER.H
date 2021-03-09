#define BYTES_PER_SCREEN	32000
#define BYTES_PER_ROW		80
#define NUM_OF_COLUMNS		200
#define NUM_OF_ROWS			400

void fill_screen(unsigned char *base, unsigned char pattern);
void clear_area(unsigned char *base, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void draw_bmp(unsigned char *base, unsigned char *img, int x, int y, unsigned int width, unsigned int height);
void draw_ground(unsigned char *base, unsigned char *img, unsigned int y, unsigned int width, unsigned int height, unsigned int offset);