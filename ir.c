#include <avr/io.h>
#include "lcd.h"
#include "math.h"

/**
 * Infrared Sensor Contorl API - Provides a set of function for controlling IR sensor
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Initialize Analogue to Digital Converter
void init_ir(void)
{
	ADMUX = 0b11000010;
	ADCSRA = 0b10000111;
}

/// Convert and Read ADC Result Value
unsigned int ADC_read(void)
{
	ADCSRA = 0b11000111;
	while(ADCSRA & 0b01000000);
	return ADC;
}

/// Convert Arbitrary Unit to Centimeters
float D_to_distance(unsigned int d)
{
	return (41510.91803 * pow(d, -1.214290489));
}

/// Master IR Scan Function
int irScan()
{
	return ((int)D_to_distance(ADC_read()));
}