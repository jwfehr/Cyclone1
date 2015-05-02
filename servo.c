/**
 * Servo Control API - provides a set of functions for controlling servo positioning
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>

// Prototypes
void init_servo();
void moveServo(int degrees);

// Global Variables
unsigned int pulse_period = 43000;				// period for pulse width modulation determined by pre-scaler (DO NOT CHANGE)
unsigned int zeroDegreePulseWidth = 745;		// pulse width corresponding to 0 degree position (#11=1125) (#8=745)
unsigned int fullDegreePulseWidth = 4055;		// pulse width corresponding to 180 degree position (#11=4800) (#8=4055)

/// Initialize Servo Motor
/**
 * Initialization function for configuring servo control registers
 */
void init_servo()
{
	OCR3A = pulse_period - 1;                   // set top value to pulse period minus one
	OCR3B = zeroDegreePulseWidth - 1;           // set compare match value to 0 degree position pulse width minus one
	TCCR3A = 0x23;                              // clear on compare match and use fast pulse width modulation mode
	TCCR3B = 0x1A;                              // use a pre-scaler of 8
	DDRE |= 0x10;                               // set pin E4 as an output
}

/// Move Servo to Given Degree
/**
 * Position the servo at the given degree as a fixed scale relative to the VORTEX platform
 * @param degrees fixed degree to which the servo will be moved
 */
void moveServo(int degrees)
{
    // use ratio of full range pulse width to determine fixed position
	OCR3B = (degrees * ((fullDegreePulseWidth-zeroDegreePulseWidth) / 180)) + zeroDegreePulseWidth - 1;
}