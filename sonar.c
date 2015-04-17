#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "math.h"

// Status Variables Used for Calculations
volatile enum{LOW, HIGH, DONE} state;
volatile unsigned int risingTime = 0;
volatile unsigned int fallingTime = 0;
volatile unsigned int overflows = 0;

// Initializes Sonar Sensor
void init_sonar() 		
{
	TCCR1A = 0b00000000;
	TCCR1B = 0b11000010;
	TIMSK  = 0b00100100;
}

// Sends Pulse to Sonar Sensor (I)
void sendPulse()
{
	cli();
	DDRD  |= 0b00010000;
	PORTD |= 0b00010000;
	wait_ms(1);
	PORTD &= 0b11101111;
	DDRD  &= 0b11101111;
	TIFR  |= 0b00100000;
	sei();
}

// Gets a Reading from Sonar Sensor (I)
unsigned int pingRead()
{
	sendPulse();
	while(state != HIGH);
	TCCR1B &= 0b10111111;
	while(state != DONE);	
	TCCR1B |= 0b01000000;
	return (fallingTime - risingTime);
}

// Converts Arbitrary Units to Centimeters (I) - may need to calibrate
unsigned int timeToDistance(unsigned int time) 
{
	return ((unsigned int)(time * 0.0085));
}

// Main Sonar Read Function - returns distance detected by sonar in centimeters
int sonarScan() 
{
	return timeToDistance(pingRead());
}

// Capture Event ISR
ISR (TIMER1_CAPT_vect)
{
	switch(state){
		case LOW:
			risingTime = ICR1;
			state = HIGH;
			break;
		case HIGH:
			fallingTime = ICR1;
			state = DONE;
			break;
		default:
			state = LOW;
			break;
	}
}

// Overflow Event ISR
ISR (TIMER1_OVF_vect)
{
	overflows++;
}