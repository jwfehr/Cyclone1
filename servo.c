/**
 * Servo Contorl API - provides a set of functions for controlling servo positioning
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/13/2015
 */

unsigned int pulse_period = 43000;              // period for pulse width modulation determined by prescaler
unsigned int zeroDegreePulseWidth = 1000;       // pulse width corresponding to 0 degree position
unsigned int fullDegreePulseWidth = 4500;       // pulse width corresponding to 180 degree position

/// Initialize Servo Motor
/**
 * Initilization function for configuring servo control registers
 */
void init_servo()
{
	OCR3A = pulse_period - 1;                   // set top value to pulse period
	OCR3B = zeroDegreePulseWidth - 1;           // set compare match value to 0 degree position pulse width
	TCCR3A = 0x23;                              // clear on compare match and use fast pulse width modulation mode
	TCCR3B = 0x1A;                              // use a prescaler of 8
	DDRE |= 0x10;                               // set pin E4 as an output
}

/// Move Servo to Given Degree
/**
 * Position the servo at the given degree as a fixed scale relative to the VORTEX platform
 * @param degrees fixed degree to which the servo will be moved
 */
void moveServo(int degrees)
{
	OCR3B = (degrees * (fullDegreePulseWidth-zeroDegreePulseWidth) / 180) - 1;  // use ratio of full range pulse width to determine fixed position
}