/*
 * test2.c
 *
 * Created: 4/20/2015 6:50:33 PM
 *  Author: jakej
 */ 

#include <avr/io.h>

#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"
#include "init.h"
#include "UI.h"

char start = 'n';
oi_t *sensorData;

int main(int argc)
{
	// Allocate memory and setup sensorData struct
	sensorData = oi_alloc();
	initAll(sensorData);


	serial_puts("Press 's' to initiate connection with robot\n\r");
	while(start != 's') // Wait for Start Command
	{
		start = serial_getc();
	}
	serial_puts("Robot communication initiated.\n\r\n\r");
	display_help();
	running_LED();
	while(1)
	{
		read_user_input_string(sensorData);
	}
	//START TRAVERSING CODE

	while("NOT DONE") //While the robot is not in the Final Zone
	{
		//TODO Interface and Movement
	}

	//TODO FLASH LEDS WHEN DONE


}