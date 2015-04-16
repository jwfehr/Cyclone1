#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

/**
 * Music Playback API - Provides a set of functions for controlling musical functions
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

///Loads the Mario flag sound to iRobot Create
/**
 *Loads the flag sound from the Mario video game franchise to the given song index
 *@param index_1 an integer from 0-15 of the index of the song on the iRobot Create
 *@param index_2 an integer from 0-15 of the index of the song on the iRobot Create
 */
void load_flag_sound(int index_1, int index_2) {
	int part_1 = index_1;		//Set index of first part of song
	int part_2 = index_2;		//Set index of second part of song
	int num_1 = 16;		//set number of notes in part 1
	int num_2 = 11;		//set number of notes in part 2
	char notes_1[num_1] = {55,60,64,72,76,79,76,56,60,63,68,72,75,80,75};		//Set notes of part 1
	char duration_1[num_1] = {9,9,9,9,9,9,26,26,9,9,9,9,9,9,26,26};			//Set duration of notes in part 1
	char notes_2[num_2] = {58,62,65,70,74,77,82,82,82,82,84};		//Set notes of part 2
	char duration_2[num_2] = {9,9,9,9,9,9,26,9,9,9,52};			//Set duration of notes in part 2
	oi_load_song(part_1, num_1, notes_1, duration_1); 		//Load part 1 to iRobot Create
	oi_load_song(part_2, num_2, notes_2, duration_2);		//Load part 2 to iRobot Create
}

///Plays the Mario flag sound
/**
 *Plays the flag sound from the Mario video game franchise
 */
void play_flag() {
	oi_t *m = oi_alloc();		//Allocate data space for open interface
	oi_init(m);		//Initialize open interface
	load_flag_sound(0,1);		//Load flag sound
	oi_play_song(0);		//Play flag part 1
	wait_ms(3313);			//Wait till end of part 1
	oi_play_song(1);		//Play flag part 2
	wait_ms(2485);		//Wait till end of part 2
}

///Plays the Mario coin sound
/**
 *Plays the coin sound from the Mario video game franchise
 */
void play_coin() {
	oi_t *m = oi_alloc();		//Allocate data space for open interface
	oi_init(m);			//Initialize open interface
	load_coin_sound(0);			//Load coin sound
	oi_play_song(0);		//Play coin sound
	wait_ms(813);		//Wait till end of coin sound
}
