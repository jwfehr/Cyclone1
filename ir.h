#ifndef IR_H
#define IR_H

#include <avr/io.h>
#include "lcd.h"
#include "math.h"

// See .c file for function descriptions
void init_ir(void);
unsigned int ADC_read(void);
float D_to_distance(unsigned int d);
int irScan();

#endif /* IR_H */
