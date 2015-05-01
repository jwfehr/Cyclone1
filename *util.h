/**
 * Util Functions - provided for us
 * @author Zhao Zhang & Chad Nelson
 * @date 06/26/2012
 */

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"

// Blocks for a specified number of milliseconds
void wait_ms(unsigned int time_val);

// Shaft encoder initialization
void shaft_encoder_init(void);

// Shaft encoder read function
char read_shaft_encoder(void);

// Initialize Stepper Motor
void stepper_init(void);

// Stepper motor move function
void move_stepper_motor_by_step(int num_steps, int direction);

// Initialize PORTC, which is used by the push buttons
void init_push_buttons(void);

// Return the position of button being pushed
char read_push_buttons(void);