#ifndef MUSIC_H
#define MUSIC_H

#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

/**
 * Music Playback API Header - Provides a set of functions for loading and playing songs
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

///Loads the Mario coin sound to iRobot Create
/**
 *Loads the coin sound from the Mario video game franchise to the given song index
 *@param index an integer from 0-15 of the index of the song on the iRobot Create
 */
void load_coin_sound(int index);

///Loads the Mario flag sound to iRobot Create
/**
 *Loads the flag sound from the Mario video game franchise to the given song index
 *@param index_1 an integer from 0-15 of the index of the song on the iRobot Create
 *@param index_2 an integer from 0-15 of the index of the song on the iRobot Create
 */
void load_flag_sound(int index_1, int index_2);

///Loads the Damage sound to iRobot Create
/**
 *Loads the damage sound from the Mario video game franchise to the given song index
 *@param index an integer from 0-15 of the index of the song on the iRobot Create
 */
void load_damage_sound(int index);

///Plays the Mario flag sound
/**
 *Plays the flag sound from the Mario video game franchise
 */
void play_flag();

///Plays the Mario coin sound
/**
 *Plays the coin sound from the Mario video game franchise
 */
void play_coin();

///Plays the damage sound
/**
 *Plays the damage sound from the Mario video game franchise
 */
void play_damage();

#endif // MUSIC_H