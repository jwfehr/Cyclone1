/**
 *  UI.c/Users/mitchell/GitHub/CPRE288 Final.c/UI.h
 
 *  @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach
      Bennett
 *  @date 4/17/15.
 
 */
#include <stdio.h>
#include <string.h>
#include "UI.h"
#include "bluetooth.h"
#include "movement.h"
#include "lcd.h"
#include <avr/io.h>


/// Reads user input
/**
 * Read user input character by character and store in char array
 * user_input_string
 *
 * @param char *user_input_string
 */
void
read_raw_UI(char *user_input_string)
{
    int cur_char;
    int i = 0;
	int j;
    
	// Clear entire user_input_string to NULL
	for (j=0; j<10; j++) {
		user_input_string[j] = '\0';
	}
	
    cur_char = serial_getc();
    serial_putc(cur_char);
    
    // Read user input until return key is pressed
    while (cur_char != 13) {
		
		if (cur_char != 127) {
			// Fill user input string with keyboard input
			user_input_string[i] = cur_char;
			i++;
		} else {
			i--;	
			user_input_string[i] = '\0';
		}
        cur_char = serial_getc();
        serial_putc(cur_char);
    }
	serial_puts("\n\r");
}

/// Display HELP information
/**
 * Prints all possible valid commands for user to interact with robot
 */
void
display_help()
{
    serial_puts("\n\rPress 'h' at any time to view a list of "
                "possible commands.\n\r\n\r");
    serial_puts("f_'int' = Move Forward 'int' centimeters\n\r");
    serial_puts("b_'int' = Move Backward 'int' centimeters\n\r");
    serial_puts("l_'int' = Turn Left 'int' degrees\n\r");
    serial_puts("r_'int' = Turn Right 'int' degrees\n\r");
    serial_puts("s = Scan 180 degrees\n\r");
}

/// Read string of user input
/**
 * Takes in a string from the user. Then parses through
 * the string, interpreting and executing commands
 */
void
read_user_input_string(oi_t *sensorData)
{
	char user_input_string[10];
	
	read_raw_UI(user_input_string);
	
    char command;
    int specifier;
    
    command = user_input_string[0];
    
    // If an integer specifier is present, read and put into 'specifier'
    if (user_input_string[1] == '_') {
        
        int i;
        int array_size;
        
        // Length of user_input_string
        array_size = strlen(user_input_string);
        char spec[array_size - 2 /*Ignore first two indices*/];
        i = 2; /*Start scanning user_input_string after first two indices*/
        
        while (user_input_string[i] != '\0') {
            spec[i-2] = user_input_string[i];
            i++;
        }

        sscanf(spec, "%d", &specifier);
    }
    
    
    /*
     * Check type of command being issued
     *
     * f = Foreward
     * b = Backward
     * l = Turn Left
     * r = Turn Right
     * s = Scan
     * h = HELP
     *
     */
	lprintf(user_input_string);
	int k;
    switch (command) {
            
            case 'f':
            moveForwardWithSensors(sensorData, specifier);
			fullScan();
            break;
            
            case 'b':
            moveBackward(sensorData, specifier);
            break;
            
            case 'l':
            turnCounterClockwise(sensorData, specifier);
            break;
            
            case 'r':
            turnClockwise(sensorData, specifier);
            break;
            
            case 's':
            fullScan();
            break;
            
            case 'h':
            display_help();
            break;
			
			case 'Q':
			finish_without_move();
			break;
			
			// If invalid command entered
			default:
			// Clear string
			for (k=0; k<10; k++) {
				user_input_string[k] = '\0';
			}
			serial_puts("Invalid Command. Press 'h' to access HELP menu\n\r");
			
    }
}