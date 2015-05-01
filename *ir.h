/**
 * Infrared Sensor Contorl API Header - Provides a set of function for controlling IR sensor
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef IR_H
#define IR_H

// Includes
#include <avr/io.h>
#include "math.h"

/// Initialize Analogue to Digital Converter
/**
 * Initilizes the digital converter used in ir scanning
 */
void init_ir();

/// Read ADC Result Value
/**
 * Reads from the IR sensor and converts to a digital value
 * @returns digital conversion result of ir sensor
 */
unsigned int ADC_read();

/// Conversion Function
/**
 * Converts arbitrary digital retun to a centimeter value as calibrated
 * @param digital the digitaly converted result of an IR pulse
 * @return the cenimeter distance equivelent of a digital input
 */
float D_to_distance(unsigned int digital);

/// Master IR Scan Function
/**
 * Returns the centimeter distacne meassured by the IR sensor
 * @return the centimeter distacne meassured by the IR sensor
 */
int irScan();

#endif // IR_H