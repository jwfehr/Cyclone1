/**
 * LED Illumination API Header - Provides a set of functions for lighting the LEDs on the iRobot Create
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef LED_H
#define LED_H

// Includes
#include <avr/io.h>
#include "util.h"
#include "open_interface.h"

/// Final LED Sequence
/**
 * Sets the LEDs to a repeating pattern to represent mission completion
 */
void final_LED_sequence();

/// Transitions LEDs to Initial Condition
/**
 * Sets LEDs to their intial conditions to represent program waiting
 */
void initial_LED();

/// Transitions LEDs to Running Condition
/**
 * Sets LEDs to their runing conditions to represent program start
 */
void running_LED();

#endif // LED_H