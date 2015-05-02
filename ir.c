/**
 * Infrared Sensor Control API - Provides a set of function for controlling IR sensor
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include "math.h"

// Prototypes
void init_ir();
unsigned int ADC_read();
float D_to_distance(unsigned int digital);
int irScan();

/// Initialize Analogue to Digital Converter
/**
 * Initilizes the digital converter used in ir scanning
 */
void init_ir()
{
	ADMUX = 0b11000010;                 // select appropriate input channel and 2.56 reference voltage
	ADCSRA = 0b10000111;                // enable ADC and use 128 prescaler
}

/// Read ADC Result Value
/**
 * Reads from the IR sensor and converts to a digital value
 * @return digital conversion result of ir sensor
 */
unsigned int ADC_read()
{
	ADCSRA = 0b11000111;                // start conversion
	while(ADCSRA & 0b01000000);         // wait for conversion to finish
	return ADC;                         // return digital conversion
}

/// Conversion Function
/**
 * Converts arbitrary digital retun to a centimeter value as calibrated
 * @param digital the digitaly converted result of an IR pulse
 * @return the cenimeter distance equivelent of a digital input
 */
float D_to_distance(unsigned int digital)
{
	return (85931 * pow(digital, -1.412));      // calibration function for robot 8
}

/// Master IR Scan Function
/**
 * Returns the centimeter distacne meassured by the IR sensor
 * @return the centimeter distacne meassured by the IR sensor
 */
int irScan()
{
	return ((int)D_to_distance(ADC_read()));    // reads IR, converts to digital, converts to centimeters
}