#include <stdio.h>
#include "RASTER.H"
#include "BOOLEAN.H"

void fill_screen(unsigned long *base, unsigned long pattern) {

	unsigned int i = 0;
	unsigned long *loc = base;

	while (i++ < LONGS_PER_SCREEN)
		*(loc++) = pattern;

}

void clear_area(unsigned long *base, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

	unsigned int long_x = x / LONG_WORD;
	unsigned int long_width = width / LONG_WORD;

	unsigned long *loc = base + y * LONGS_PER_ROW + long_x;
	unsigned char start_bit = x % LONG_WORD;
	unsigned char end_bit = LONG_WORD - start_bit;

	unsigned int img_x;
	unsigned int img_y;

	unsigned long start_mask = 0xFFFFFFFFu << end_bit;
	unsigned long end_mask = 0xFFFFFFFFu >> start_bit + width % LONG_WORD;		/* width % 32 (byte alignment???) untested */

	for (img_y = 0; img_y < height; img_y++) {
		
		if (start_bit > 0)												/* decides if beginning is long aligned */
			*loc &= start_mask;
		else
			*loc = 0;
		loc++;

		for (img_x = 1; img_x < long_width; img_x++)					/* clear row */
			*(loc++) = 0;

		if (start_bit > 0)												/* decide if end is long aligned */
			*loc &= end_mask;
		else
			*loc = 0;

		loc += LONGS_PER_ROW - long_width;								/* move to next line */
	}
}

void draw_bmp(unsigned long *base, unsigned long *img, signed int x, signed int y, unsigned int width, unsigned int height) {

	unsigned int cropped_up = 0;
	unsigned int cropped_down = 0;
	unsigned int cropped_left = 0;
	unsigned int cropped_right = 0;

	signed int long_x = x / LONG_WORD;
	signed int long_width = width / LONG_WORD;

	unsigned int start_bit;
	unsigned int end_bit;

	unsigned long *loc;

	unsigned int img_x;
	unsigned int img_y;

	if (y > NUM_OF_ROWS)
		return;

	if (y + height < 0)
		return;

	if (long_x >= LONGS_PER_ROW)
		return;

	if (long_x + long_width <= 0)
		return;

	if (y < 0) {
		cropped_up = -y;
		y = 0;
		img += cropped_up * long_width;
	}

	if (y + height > NUM_OF_ROWS) {
		cropped_down = y + height - NUM_OF_ROWS;
	}

	if (x < 0) {
		cropped_left = -long_x;
		long_x = LONGS_PER_ROW;
		long_width -= cropped_left;
		x = LONG_WORD + x;
	}

	if (start_bit == 0 && long_x + long_width > LONGS_PER_ROW)
		cropped_right = long_x + long_width - LONGS_PER_ROW;
	else if (start_bit > 0 && long_x + long_width + 1 > LONGS_PER_ROW)
		cropped_right = long_x + long_width + 1 - LONGS_PER_ROW;

	start_bit = x % LONG_WORD;
	end_bit = LONG_WORD - start_bit;

	loc = base + y * LONGS_PER_ROW + long_x;

	for (img_y = cropped_up; img_y < height - cropped_down; img_y++) {	/* y loop */
		img += cropped_left;
		if (start_bit > 0 && cropped_left > 0) {
			*loc |= *(img - 1) << end_bit;
		}
		img_x = 0;
		if (cropped_right > 0)
			img_x = cropped_right + 1;
		for (; img_x < long_width; img_x++) {							/* x loop */
			*(loc++) |= *img >> start_bit;								/* draw high order slice of the image long */
			if (end_bit > 0)
				*loc |= *img << end_bit;								/* draw low order slice of the image long */
			img++;
		}
		if (cropped_right > 0)
			*loc |= *img >> start_bit;

		loc += LONGS_PER_ROW - long_width + cropped_right;				/* move to next line */
		img += cropped_right;
	}
}

void draw_ground(unsigned long *base, unsigned long *img, unsigned int y, unsigned int width, unsigned int height, unsigned int offset) {

	unsigned int long_width = width / LONG_WORD;
	unsigned int long_offset = offset / LONG_WORD;

	unsigned int start_bit = offset % LONG_WORD;
	unsigned int end_bit = LONG_WORD - start_bit;

	unsigned long *loc = base + y * LONGS_PER_ROW;
	unsigned long *img_loc = img + long_width - long_offset;

	unsigned int img_x;
	unsigned int img_y;

	for (img_y = 0; img_y < height; img_y++) {							/* height of ground */
		for (img_x = 0; img_x < long_offset; img_x++) {					/* draw line */
			if (start_bit > 0)											
				*loc |= *(img_loc - 1) << end_bit;						/* draw end of out of alignment byte */
			*(loc++) |= *(img_loc++) >> start_bit;						/* draw beginning of out of alignment byte */
		}
		if (start_bit > 0)												/* draw last byte */
			*loc |= *(img_loc - 1) << end_bit;
		img_loc += long_width - long_offset;
		loc += LONGS_PER_ROW - long_offset;
	}

	loc = base + y * LONGS_PER_ROW + long_offset;						/* move to second half of ground */
	img_loc = img;

	for (img_y = 0; img_y < height; img_y++) {							/* same as before but for the second half of ground */
		for (img_x = 0; img_x < long_width - long_offset; img_x++) {
			*(loc++) |= *img_loc >> start_bit;
			if (start_bit > 0)
				*loc |= *img_loc << end_bit;
			img_loc++;
		}
		img_loc += long_width - (long_width - long_offset);
		loc += LONGS_PER_ROW - (long_width - long_offset);
	}
}