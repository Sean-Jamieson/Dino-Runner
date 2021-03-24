#include <stdio.h>
#include <osbind.h>
#include "FBUFF.H"
#include "RASTER.H"
#include "BOOLEAN.H"

unsigned long buff1Arr[LONGS_PER_SCREEN + 8];
unsigned long buff2Arr[LONGS_PER_SCREEN + 8];
unsigned long* buff1 = 0;
unsigned long* buff2 = 0;
unsigned long* o_buffer;	/* Original screen buffer */
int o_res;					/* Original resolution */
bool useBuff1 = true;

void fb_init() {

	buff1 = Physbase();2

	buff1 = (unsigned long*)(((long)(&buff1Arr) | 0xff) + 1);
	buff2 = (unsigned long*)(((long)(&buff2Arr) | 0xff) + 1);

	o_buffer = Physbase();
	o_res = Getrez();
	Setscreen(Logbase(), buff1, 2);
}

void fb_exit() {
	Setscreen(Logbase(), o_buffer, o_res);
}

void fb_flip() {
	unsigned long *buff;
	if (useBuff1 == true) {
		useBuff1 = false;
		buff = buff2;
	} else {
		useBuff1 = true;
		buff = buff1;
	}

	Setscreen(Logbase(), buff, 2);
}

unsigned long* fb_get_buff() {
	if (useBuff1 == true)
		return buff2;
	else
		return buff1;
}