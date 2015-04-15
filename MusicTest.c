/*
 * MusicTest.c
 *
 * Created: 4/14/2015 9:54:23 PM
 *  Author: zwbce
 */ 

#include "music.h"
#include "open_interface.h"

#include <avr/io.h>

int main(void)
{
	oi_t *m = oi_alloc();
	oi_init(m);
	load_coin_sound(0);
	oi_play_song(0);
}