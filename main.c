/**
 * Main Fuction Control - launching point for all sytem code intilization, function, and command
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 6/1/2015
 */ 

// Includes
#include <avr/io.h>
#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"
#include "init.h"
#include "ui.h"

// Global Variables
char start = 'n';
oi_t *sensorData;

/// Main Function
/**
 * Main function in which all other code functions. Handles initilization, startup, and code performance
 */
void main()
{
	sensorData = oi_alloc();                                                // allocate memeory for struct
	initAll(sensorData);                                                    // initilize all systems

	serial_puts("Press 's' to initiate connection with robot\n\r");         // wait for start command
	while(start != 's')
	{
		start = serial_getc();
	}
    
	serial_puts("Robot communication initiated.\n\r\n\r");                  // proceed with startup
	display_help();                                                         // display help information
	running_LED();                                                          // swich to running led
	
    while(1)
	{
		read_user_input_string(sensorData);                                 // main function body loop
	}
}