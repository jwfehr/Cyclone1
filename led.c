/**
 * LED Illumination API - Provides a set of functions for lighting the LEDs on the iRobot create
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include "util.h"
#include "open_interface.h"

// Prototypes
void final_LED_sequence();
void initial_LED();
void running_LED();

/// Final LED Sequence
/**
 * Sets the LEDs to a repeating pattern to represent mission completion
 */
void final_LED_sequence()
{
	char power_color = 0;           // power LED color to green
	char advance_play_led = 0;      // advance play LED off
	char intensity = 255;           // set intenity value to maximum
    
	while(1)                        // continually cycle
    {
		for (power_color; power_color < 255; ++power_color)     // cycle through full intensity level upward
        {
            if(advance_play_led == 0)                           // switch led on/off position
            {
				advance_play_led = 1;
			}
			else
            {
				advance_play_led = 0;
			}
			oi_set_leds(advance_play_led, advance_play_led, power_color, intensity);    // set LEDs
			wait_ms(10);                                                                // wait 10 ms
		}
		for (power_color; power_color > 0; --power_color)       // cycle through full intensity level downward
        {
			if(advance_play_led == 0)                           // switch led on/off position
            {
				advance_play_led = 1;
			}
			else
            {
				advance_play_led = 0;
			}
			oi_set_leds(advance_play_led, advance_play_led, power_color, intensity);    // set LEDs
			wait_ms(10);                                                                // wait 10 ms
		}
	}
}

/// Transitions LEDs to Initial Condition
/**
 * Sets LEDs to their intial conditions to represent program waiting
 */
void initial_LED()
{
	oi_set_leds(255, 255, 255, 255);    // all lights on
}

/// Transitions LEDs to Running Condition
/**
 * Sets LEDs to their runing conditions to represent program start
 */
void running_LED()
{
	oi_set_leds(0,0,0,255);             // power to red, all others off
}