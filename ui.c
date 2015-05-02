/**
 *  UI Control API - Provides a set of functions for controlling all other code using transmitions via bluetooth
 *  @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 *  @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include <string.h>
#include "ui.h"
#include "bluetooth.h"
#include "movement.h"
#include "lcd.h"

/// Reads User Input
/**
 * Read user input character by character and store in char array user_input_string
 * @param user_input_string string for storing values
 */
void read_raw_UI(char* user_input_string)
{
    int cur_char;                               // local variables
    int i = 0;
    
    int j;
	for (j=0; j<10; j++)                        // Clear entire user_input_string to NULL
    {
		user_input_string[j] = '\0';
	}
	
    cur_char = serial_getc();                   // recieve and store character
    serial_putc(cur_char);                      // transmit back letter for echo
    
    while (cur_char != 13) {                    // Read user input until return key is pressed
		if (cur_char != 127) {                  // if valid character
			user_input_string[i] = cur_char;    // fill user input string with input
			i++;                                // increment position
		} else {                                // if invalid character
			i--;                                // decrement index
			user_input_string[i] = '\0';        // and set to end string
		}
        cur_char = serial_getc();               // get new char
        serial_putc(cur_char);                  // transmition echo
    }
	serial_puts("\n\r");                        // transmit newline and return
}

/// Display Help Information
/**
 * Prints all possible valid commands for user to interact with robot
 */
void display_help()
{
    serial_puts("\n\rPress 'h' at any time to view a list of possible commands.\n\r\n\r");
    serial_puts("f_'int' = Move Forward 'int' centimeters\n\r");
    serial_puts("b_'int' = Move Backward 'int' centimeters\n\r");
    serial_puts("l_'int' = Turn Left 'int' degrees\n\r");
    serial_puts("r_'int' = Turn Right 'int' degrees\n\r");
    serial_puts("s = Scan 180 degrees\n\r");
}

/// Read string of user input
/**
 * Takes in a string from the user then parses through the string interpreting and executing commands
 * @param sensorData struct of sensor data
 */
void read_user_input_string(oi_t* sensorData)
{
	char user_input_string[10];                         // string for input
	read_raw_UI(user_input_string);                     // read in input string
    char command;                                       // local variables
    int specifier;
    command = user_input_string[0];                     // take in first character of string
    
    if (user_input_string[1] == '_')                    // check for and read in specifier
    {
        int i;
        int array_size = strlen(user_input_string);
        char spec[array_size - 2];                      // ignore first two indeces
        i = 2;                                          // start scanning user_input_string
        while (user_input_string[i] != '\0')
        {
            spec[i-2] = user_input_string[i];
            i++;
        }
        sscanf(spec, "%d", &specifier);
    }
    
	lprintf(user_input_string);
	int k;                                              // Check type of command being issued
    switch (command) {
        case 'f':                                       // f = forward
            moveForwardWithSensors(sensorData, specifier);
            break;
        case 'b':                                       // b = backward
            moveBackward(sensorData, specifier);
            break;
        case 'l':                                       // l = left turn
            turnCounterClockwise(sensorData, specifier);
            break;
        case 'r':                                       // r = right turn
            turnClockwise(sensorData, specifier);
            break;
        case 's':                                       // s = scan
            fullScan();
            break;
        case 'h':                                       // h = help
            display_help();
            break;
        case 'Q':                                       // Q = finish
			finish_without_move();
			break;
        default:
			for (k=0; k<10; k++)                        // clear string
            {
				user_input_string[k] = '\0';
			}
			serial_puts("Invalid Command. Press 'h' to access HELP menu\n\r");
			
    }
}