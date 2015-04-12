#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

/**
 * Music Playback API - Provides a set of functions for controlling bluetooth communications
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Sets Up a Variety of Songs
void load_coin_sound(int index) {
	int song_index = index;
	int num_notes = 2;
	char notes[2] = {83, 88};
	char duration[2] = {2, 10};
	oi_load_song(song_index, num_notes, notes, duration);
}