#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

/**
 * Music Playback API - Provides a set of functions for controlling bluetooth communications
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Sets Up a Variety of Songs

///Loads the Mario coin sound to iRobot Create
/**
 *Loads the coin sound from the Mario video game franchise to the given song index
 *@param index an integer from 0-15 of the index of the song on the iRobot Create
 */
void load_coin_sound(int index) {
	int song_index = index;									//Int variable to store index of song
	int num_notes = 2;										//Total number of notes in the song
	char notes[2] = {83, 88};								//Array containing the specified notes
	char duration[2] = {7, 45};								//Array containing the durations of the specified notes
	oi_load_song(song_index, num_notes, notes, duration);	//Load song given by values assigned above onto the iRobot Create
}