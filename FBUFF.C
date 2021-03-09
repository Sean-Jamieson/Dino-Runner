#include <osbind.h>
#include "FBUFF.H"
#include "RASTER.H"
#include "BOOLEAN.H"

unsigned char buff1[BYTES_PER_SCREEN];
unsigned char buff2[BYTES_PER_SCREEN];
unsigned char *o_buffer;
unsigned int o_res;
bool useBuff1 = true;

void fb_init() {
	o_buffer = Physbase();
	o_res = Getrez();
	Setscreen(Logbase(), buff1, 2);
}

void fb_exit() {
	Setscreen(Logbase(), o_buffer, o_res);
}

void fb_flip() {
	unsigned char *buff;
	if (useBuff1 == true) {
		useBuff1 = false;
		buff = buff2;
	} else {
		useBuff1 = true;
		buff = buff1;
	}

	Setscreen(Logbase(), buff, 0);
}

unsigned char* fb_get_buff() {
	if (useBuff1 == true)
		return buff2;
	else
		return buff1;
}