/**
 *  UI Control API - Provides a set of functions for controlling all other code using transmitions via bluetooth
 *  @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 *  @date 5/1/2015
 */

#ifndef UI_H
#define UI_H

// Includes
#include <avr/io.h>
#include <string.h>
#include "UI.h"
#include "bluetooth.h"
#include "movement.h"
#include "lcd.h"

/// Reads User Input
/**
 * Read user input character by character and store in char array user_input_string
 * @param user_input_string string for storing values
 */
void read_raw_UI(char* user_input_string);

/// Display Help Information
/**
 * Prints all possible valid commands for user to interact with robot
 */
void display_help();

/// Read string of user input
/**
 * Takes in a string from the user then parses through the string interpreting and executing commands
 * @param sensorData struct of sensor data
 */
void read_user_input_string(oi_t* sensorData);
    
#endif // UI_H