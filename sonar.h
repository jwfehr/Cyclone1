#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>
#include "lcd.h"
#include "math.h"

// See .c file for function descriptions
void init_sonar();		
void sendPulse();
unsigned int pingRead();
unsigned int timeToDistance(unsigned int time);
int sonarScan();

#endif // SONAR_H