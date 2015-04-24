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
/**
 *Turns on LED lights signifying reaching the retrieval area of the course.
 *The LED light at the Power Button will transition from Green to Red and back repeatedly until the robot is turned off.
 *The two other LED lights will flash repeatedly until robot is turned off.
 */
void final_LED_sequence(void) {
	char power_color = 0;
	char advance_play_led = 0;
	char intensity = 255;
	
	while(1) {
		for (power_color; power_color < 255; ++power_color) {
			if(advance_play_led == 0) {
				advance_play_led = 1;
			}
			else {
				advance_play_led = 0;
			}
			oi_set_leds(advance_play_led, advance_play_led, power_color, intensity);
			wait_ms(10);
		}
		for (power_color; power_color > 0; --power_color) {
			if(advance_play_led == 0) {
				advance_play_led = 1;
			}
			else {
				advance_play_led = 0;
			}
			oi_set_leds(advance_play_led, advance_play_led, power_color, intensity);
			wait_ms(10);
		}
	}
}

///Turns on LED lights to signify that the iRobot Create is waiting for the start command
/**
 *Turns on LEDs to show that it is in waiting for the start command to be transmitted
 *Power LED will be red, all other LEDs will be off
 */
void initial_LED(void) {
	oi_set_leds(255, 255, 255, 255);
}

///Turns on LED lights to signify that the iRobot Create has recieved start command and has not finished the course
/**
 *Turns on LEDs to show that start command has been given and the robot has not completed the course
 *Power LED will be (NOT SURE), all other LEDs will be off
 */
void running_LED(void) {
	oi_set_leds(0,0,0,255);
}