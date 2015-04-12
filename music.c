///Sets up a variety of songs

#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

void load_coin_sound(int index) {
	int song_index = index;
	int num_notes = 2;
	char notes[2] = {83, 88};
	char duration[2] = {2, 10};
	
	oi_load_song(song_index, num_notes, notes, duration);
}