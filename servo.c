/**
 * Servo Contorl API - Provides a set of functions for controlling servo positioning
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

unsigned int pulse_period = 43000;
unsigned int zeroDegreePulseWidth = 1000;
unsigned int fullDegreePulseWidth = 4500;

/// Initialize Servo Motor
void init_servo()
{
	OCR3A = pulse_period - 1;
	OCR3B = zeroDegreePulseWidth - 1;
	TCCR3A = 0x23;
	TCCR3B = 0x1A;
	DDRE |= 0x10;
}

/// Move Servo to Given Degree
void moveServo(int degrees)
{
	OCR3B = (degrees * (fullDegreePulseWidth-zeroDegreePulseWidth) / 180) - 1;
}