#ifndef LED_H
#define LED_H

#include <stdlib.h>
#include <avr/io.h>
#include "util.h"
#include "open_interface.h"

/**
 * LED Illumination API Header - Provides a set of functions for lighting the LEDs on the iRobot Create
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/18/2015
 */

///Turns on LED lights on iRobot Create to signify reaching the final zone
void final_LED_sequence(void);

///Turns on LED lights to signify that the iRobot Create is waiting for the start command
void initial_LED(void);

///Turns on LED lights to signify that the iRobot Create has recieved start command and has not finished the course
void running_LED(void);

#endif // LED_H