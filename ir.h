#ifndef IR_H
#define IR_H

/**
 * Infrared Sensor Contorl API - Provides a set of function for controlling IR sensor
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Initialize Analogue to Digital Converter
void init_ir(void);

/// Convert and REad ADC Result Value
unsigned int ADC_read(void);

/// Convert Arbitrary Unity to Centimeters
float D_to_distance(unsigned int d);

/// Master IR Scan Function
int irScan();

#endif // IR_H