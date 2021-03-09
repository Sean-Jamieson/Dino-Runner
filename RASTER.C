#include "RASTER.H"
#include "BOOLEAN.H"

void fill_screen(unsigned char *base, unsigned char pattern) {

	unsigned int i = 0;
	unsigned char *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}

void clear_area(unsigned char *base, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

	unsigned int byte_x = x / 8;
	unsigned int byte_width = width / 8;

	unsigned char *loc = base + y * BYTES_PER_ROW + byte_x;
	unsigned char start_bit = x % 8;
	unsigned char end_bit = 8 - start_bit;

	unsigned int img_x;
	unsigned int img_y;

	unsigned char start_mask = 0xFFu << end_bit;
	unsigned char end_mask = 0xFFu >> start_bit + width % 8;

	for (img_y = 0; img_y < height; img_y++) {
		
		if (start_bit > 0)
			*loc &= start_mask;
		else
			*loc = 0;
		loc++;

		for (img_x = 1; img_x < byte_width; img_x++) {
			*(loc++) = 0;
		}

		if (end_bit > 0)
			*loc &= end_mask;
		else
			*loc = 0;
		loc++;

		loc += BYTES_PER_ROW - byte_width;
	}
}

void draw_bmp(unsigned char *base, unsigned char *img, int x, int y, unsigned int width, unsigned int height) {

	unsigned int cropped_x = 0;

	int byte_x = x / 8;
	int byte_width = width / 8;

	unsigned int start_bit = x % 8;
	unsigned int end_bit = 8 - start_bit;

	unsigned char *loc = base + y * BYTES_PER_ROW + byte_x;

	unsigned int img_x;
	unsigned int img_y;

	if (x < 0) {
		byte_width += byte_x;
		cropped_x = -byte_x;
		byte_x = 0;
	}

	for (img_y = 0; img_y < height; img_y++) {
		img += cropped_x;
		for (img_x = 0; img_x < byte_width; img_x++) {
			*(loc++) |= *img >> start_bit;
			if (end_bit > 0)
				*loc |= *img << end_bit;
			img++;
		}
		loc += BYTES_PER_ROW - byte_width;
	}
}

void draw_ground(unsigned char *base, unsigned char *img, unsigned int y, unsigned int width, unsigned int height, unsigned int offset) {

	unsigned int byte_width = width / 8;
	unsigned int byte_offset = offset / 8;

	unsigned int start_bit = offset % 8;
	unsigned int end_bit = 8 - start_bit;

	unsigned char *loc = base + y * BYTES_PER_ROW;
	unsigned char *img_loc = img + byte_width - byte_offset;

	unsigned int img_x;
	unsigned int img_y;

	for (img_y = 0; img_y < height; img_y++) {
		for (img_x = 0; img_x < byte_offset; img_x++) {
			if (start_bit > 0)
				*loc |= *(img_loc - 1) << end_bit;
			*(loc++) |= *(img_loc++) >> start_bit;
		}
		if (start_bit > 0)
			*loc |= *(img_loc - 1) << end_bit;
		img_loc += byte_width - byte_offset;
		loc += BYTES_PER_ROW - byte_offset;
	}

	loc = base + y * BYTES_PER_ROW + byte_offset;
	img_loc = img;

	for (img_y = 0; img_y < height; img_y++) {
		for (img_x = 0; img_x < byte_width - byte_offset; img_x++) {
			*(loc++) |= *img_loc >> start_bit;
			if (start_bit > 0)
				*loc |= *img_loc << end_bit;
			img_loc++;
		}
		img_loc += byte_width - (byte_width - byte_offset);
		loc += BYTES_PER_ROW - (byte_width - byte_offset);
	}
}