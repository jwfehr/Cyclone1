/**
 * Sonar Control API Header - Provides a set of functions for controlling sonar scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/21/2015
 */

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef SONAR_H
#define SONAR_H

/// Initialization Function for Sonar Sensor
/**
 * Configures the associated registers used for sonar sensor
 */
void init_sonar();

/// Send Startup Pulse
/**
 * Sends a 1 millisecond pulse into the servo unit for startup.
 */	
void sendPulse();

/// Read Sonar Sensor Response
/**
 * Sends the sonar sensor a startup pulse, waits for rising and falling response edge, and returns pulse time
 * @return the time between falling edge and rising edge events representative of sonar distance
 */
unsigned int pingRead();


unsigned int timeToDistance(unsigned int time);


int sonarScan();

#endif // SONAR_H