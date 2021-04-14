#define BYTES_PER_SCREEN	32000
#define LONGS_PER_SCREEN	8000
#define BYTES_PER_ROW		80
#define LONGS_PER_ROW		20
#define NUM_OF_COLUMNS		640
#define NUM_OF_ROWS			400
#define LONG_WORD           32


void fill_screen(unsigned long *base, unsigned long pattern);
void clear_area(unsigned long *base, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void draw_bmp(unsigned long *base, unsigned long *img, signed int x,signed int y, unsigned int width, unsigned int height);
void draw_ground(unsigned long *base, unsigned long *img, unsigned int y, unsigned int width, unsigned int height, unsigned int offset);