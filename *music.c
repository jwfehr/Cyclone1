/**
 * Music Playback API - Provides a set of functions for controlling musical functions
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include "util.h"
#include "open_interface.h"

// Prototypes
void load_coin_sound(int index);
void load_flag_sound(int index_1, int index_2);
void load_damage_sound(int index);
void play_damage();
void play_flag();
void play_coin();

/// Loads the Mario Coin Sound into the Robot
/**
 * Loads the coin sound from the Mario video game franchise to the given song index
 * @param index an integer from 0-15 of the index of the song on the robot
 */
void load_coin_sound(int index)
{
	int song_index = index;									// variable to store index of song
	int num_notes = 2;										// total number of notes in the song
	char notes[2] = {83, 88};								// array containing the specified notes
	char duration[2] = {7, 45};								// array containing the durations of the specified notes
	oi_load_song(song_index, num_notes, notes, duration);	// load song given by values assigned above onto the robot
}

/// Loads the Mario Flag Sound into the Robot
/**
 * Loads the flag sound from the Mario video game franchise to the given song index
 * @param index_1 an integer from 0-15 of the index of the song on the robot
 * @param index_2 an integer from 0-15 of the index of the song on the robot
 */
void load_flag_sound(int index_1, int index_2)
{
	int part_1 = index_1;                                                   // set index of first part of song
	int part_2 = index_2;                                                   // set index of second part of song
	int num_1 = 16;                                                         // set number of notes in part 1
	int num_2 = 11;                                                         // set number of notes in part 2
	char notes_1[16] = {55,60,64,72,76,79,76,56,60,63,68,72,75,80,75};		// set notes of part 1
	char duration_1[16] = {9,9,9,9,9,9,26,26,9,9,9,9,9,9,26,26};			// set duration of notes in part 1
	char notes_2[11] = {58,62,65,70,74,77,82,82,82,82,84};                  // set notes of part 2
	char duration_2[11] = {9,9,9,9,9,9,26,9,9,9,52};                        // set duration of notes in part 2
	oi_load_song(part_1, num_1, notes_1, duration_1);                       // load part 1 onto robot
	oi_load_song(part_2, num_2, notes_2, duration_2);                       // load part 2 onto robot
}

/// Loads the Damage Sound into the Robot
/**
 * Loads the damage sound from the Mario video game franchise to the given song index
 * @param index an integer from 0-15 of the index of the song into the robot
 */
void load_damage_sound(int index)
{
	int song_index = index;                                         // variable to store index of song
	int num_notes = 11;                                             // total number of notes in the song
	char notes[11] = {57, 52, 45, 1, 57, 52, 45, 1, 57, 52, 45,};   // array containing the specified notes
	char duration[11] = {4, 4, 4, 12, 4, 4, 4, 12, 4, 4, 4};        // array containing the durations of the specified notes
	oi_load_song(song_index, num_notes, notes, duration);           // load song given by values assigned above onto the robot
}

/// Plays the Damage Sound
/**
 * Plays the damage sound from the Mario video game franchise
 */
void play_damage()
{
	load_damage_sound(0);	// load damage sound
	oi_play_song(0);		// play damage sound
	wait_ms(938);           // wait until the end of damage sound
}

/// Plays the Mario Flag Sound
/**
 * Plays the flag sound from the Mario video game franchise
 */
void play_flag()
{
	load_flag_sound(0,1);	// load flag sound
	oi_play_song(0);		// play flag part 1
	wait_ms(3313);			// wait until the end of part 1
	oi_play_song(1);		// play flag part 2
	wait_ms(2485);          // wait until the end of part 2
}

/// Plays the Mario Coin Sound
/**
 * Plays the coin sound from the Mario video game franchise
 */
void play_coin()
{
	load_coin_sound(0);		// load coin sound
	oi_play_song(0);		// play coin sound
	wait_ms(813);           // wait until the end of coin sound
}