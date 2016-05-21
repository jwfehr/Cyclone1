/**
 * Music Playback API Header - Provides a set of functions for controlling musical functions
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef MUSIC_H
#define MUSIC_H

// Includes
#include "util.h"
#include "open_interface.h"

/// Loads the Mario Coin Sound into the Robot
/**
 * Loads the coin sound from the Mario video game franchise to the given song index
 * @param index an integer from 0-15 of the index of the song on the robot
 */
void load_coin_sound(int index);

/// Loads the Mario Flag Sound into the Robot
/**
 * Loads the flag sound from the Mario video game franchise to the given song index
 * @param index_1 an integer from 0-15 of the index of the song on the robot
 * @param index_2 an integer from 0-15 of the index of the song on the robot
 */
void load_flag_sound(int index_1, int index_2);

/// Loads the Damage Sound into the Robot
/**
 * Loads the damage sound from the Mario video game franchise to the given song index
 * @param index an integer from 0-15 of the index of the song into the robot
 */
void load_damage_sound(int index);

/// Plays the Damage Sound
/**
 * Plays the damage sound from the Mario video game franchise
 */
void play_damage();

/// Plays the Mario Flag Sound
/**
 * Plays the flag sound from the Mario video game franchise
 */
void play_flag();

/// Plays the Mario Coin Sound
/**
 * Plays the coin sound from the Mario video game franchise
 */
void play_coin();

#endif // MUSIC_H