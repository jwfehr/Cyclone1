/**
 * Util Functions - provided for us
 * @author Zhao Zhang & Chad Nelson
 * @date 06/26/2012
 */

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"

// Global used for interrupt driven delay functions
volatile unsigned int timer2_tick;
void timer2_start(char unit);
void timer2_stop();

// Blocks for a specified number of milliseconds
void wait_ms(unsigned int time_val)
{
	OCR2=250;
	timer2_tick=0;
	timer2_start(0);
	while(timer2_tick < time_val);
	timer2_stop();
}

// Start timer2
void timer2_start(char unit)
{
	timer2_tick=0;
	if ( unit == 0 )
    {
        TCCR2=0b00001011;
        TIMSK|=0b10000000;
	}
	if (unit == 1)
    {
        TCCR2=0b00001001;
        TIMSK|=0b10000000;
	}
	sei();
}

// Stop timer2
void timer2_stop()
{
	TIMSK&=~0b10000000;
	TCCR2&=0b01111111;
}

// Interrupt handler (runs every 1 ms)
ISR (TIMER2_COMP_vect)
{
	timer2_tick++;
}

// Initialize PORTC to accept push buttons as input
void init_push_buttons(void)
{
	DDRC &= 0xC0;
	PORTC |= 0x3F;
}

// Return the position of button being pushed
char read_push_buttons(void)
{
	unsigned char in = PINC;
	if(!(in&0b00100000))
	{
		return 6;	
	}
	if(!(in&0b00010000))
	{
		return 5;
	}
	if(!(in&0b00001000))
	{
		return 4;
	}
	if(!(in&0b00000100))
	{
		return 3;
	}
	if(!(in&0b00000010))
	{
		return 2;
	}
	if(!(in&0b00000001))
	{
		return 1;
	}
	return 0;
}

// Initialize PORTC for input from the shaft encoder
void shaft_encoder_init(void)
{
	DDRC &= 0x3F;
	PORTC |= 0xC0;
}

// Read the shaft encoder
char read_shaft_encoder(void)
{
	static unsigned char old_value = 0xC0;
	unsigned char new_value = PINC&0xC0;
	char rotation = 0;
	if (old_value == 0xC0)
    {
		if (new_value == 0x40)
			rotation = 1;
		if (new_value == 0x80)
			rotation = -1;
	}
	old_value = new_value;
	return rotation;
}

// Initialize PORTE to control the stepper motor
void stepper_init(void)
{
	DDRE |= 0xF0;
	PORTE &= 0x8F;
	wait_ms(2);
	PORTE &= 0x0F;
}

// Turn the Stepper Motor
void  move_stepper_motor_by_step(int num_steps, int direction)
{
	if(direction == 1)
	{
		for(int i = 0; i < num_steps; i++)
		{
			PORTE = ((PORTE&0x0F)| 0b00010000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b00100000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b01000000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b10000000);
			wait_ms(20);  
			PORTE = ((PORTE&0x0F)| 0b00010000);
			wait_ms(20);
		}
	}
	else if(direction == -1)
	{
		for(int i = 0; i < num_steps; i++)
		{
			PORTE = ((PORTE&0x0F)| 0b00010000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b10000000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b01000000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b00100000);
			wait_ms(20);
			PORTE = ((PORTE&0x0F)| 0b00010000);
			wait_ms(20);
		}	
	}
    PORTE = ((PORTE&0x0F)| 0b00000000);
}