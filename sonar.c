/**
 * Sonar Control API - Provides a set of functions for controlling sonar scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/21/2015
 */

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>

// Prototypes
void init_sonar();
void sendPulse();
unsigned int pingRead();
unsigned int timeToDistance(unsigned int time);
int sonarScan();

// Global Variables
volatile enum{LOW, HIGH, DONE} state;		// enum used to represent the state of the pulse
volatile unsigned int risingTime = 0;		// recorded time of rising edge event
volatile unsigned int fallingTime = 0;		// recorded time of falling edge event
volatile unsigned int overflows = 0;		// number of recorder timer overflows

/// Initialization Function for Sonar Sensor
/**
 * Configures the associated registers used for sonar sensor
 */
void init_sonar()
{
	TCCR1A = 0b00000000;		// input capture mode
	TCCR1B = 0b11000010;		// used noise canceler, rising edge capture, 8 pre-scaler
	TIMSK  = 0b00100100;		// enables input capture interrupt
}

/// Send Startup Pulse
/**
 * Sends a 1 millisecond pulse into the servo unit for startup.
 */
void sendPulse()
{
	cli();						// disable all interrupts
	DDRD  |= 0b00010000;		// set data direction to outgoing
	PORTD |= 0b00010000;		// output a 1
	wait_ms(1);					// wait one millisecond for sonar
	PORTD &= 0b11101111;		// output a 0
	DDRD  &= 0b11101111;		// set data direction to incoming
	TIFR  |= 0b00100000;		// clear the input capture flag using a one
	sei();						// enable all interrupts
}

/// Read Sonar Sensor Response
/**
 * Sends the sonar sensor a startup pulse, waits for rising and falling response edge, and returns pulse time
 * @return the time between falling edge and rising edge events representative of sonar distance
 */
unsigned int pingRead()
{
	sendPulse();						// send startup pulse
	while(state != HIGH);				// wait for rising edge event
	TCCR1B &= 0b10111111;				// switch to falling edge capture mode
	while(state != DONE);				// wait for falling edge event
	TCCR1B |= 0b01000000;				// switch to rising edge capture mode
	return (fallingTime - risingTime);	// return time between falling and rising events
}

/// Converts Arbitrary Units to Centimeters
/**
 * Using a calibrated function to determine distance from sonar time response
 * @return the associated centimeter distance of some time value
 */
unsigned int timeToDistance(unsigned int time)
{
	return ((unsigned int)(((time * 0.0086)-8.1198)+1));	// uses a calibration function to convert sonar time to distance for ROBOT8
}

/// Main Sonar Read Function
/**
 * Sends a startup pulse, reads the return pulse, calculates the time, and converts to a centimeter distance
 * @return distance detected by sonar in centimeters
 */
int sonarScan()
{
	return timeToDistance(pingRead());	// converts the time returned by a sonar pulse to centimeters
}

/// Capture Event ISR
ISR (TIMER1_CAPT_vect)
{
	switch(state){
		case LOW:				// if event occurs and low
			risingTime = ICR1;		// record rising edge time
			state = HIGH;			// set state to high
			break;
		case HIGH:				// if event occurs and high
			fallingTime = ICR1;		// recording falling edge time
			state = DONE;			// set state to done
			break;
		default:				// if event occurs and done
			state = LOW;			// set state to low
			break;
	}
}

/// Overflow Event ISR
ISR (TIMER1_OVF_vect)
{
	overflows++;	// increment overflow count if an overflow occurs
}