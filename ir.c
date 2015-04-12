#include <avr/io.h>
#include "lcd.h"
#include "math.h"

/// Initialize Analogue to Digital Converter
void init_ir(void)
{
	ADMUX = 0b11000010;
	ADCSRA = 0b10000111;
}

/// Convert and Read ADC Result Value
// may need to add channel selection in the future
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

int irScan()  //All encumpusing function scans with ir sensor, returns a value in centimeters for the distance measured by the ir sensor
{
	return ((int)D_to_distance(ADC_read()));
}
