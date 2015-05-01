/**
 * Sonar Control API Header - Provides a set of functions for controlling sonar scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef SONAR_H
#define SONAR_H

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>

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

/// Converts Arbitrary Units to Centimeters
/**
 * Using a calibrated function to determine distance from sonar time response
 * @return the associated centimeter distance of some time value
 */
unsigned int timeToDistance(unsigned int time);

/// Main Sonar Read Function
/**
 * Sends a startup pulse, reads the return pulse, calculates the time, and converts to a centimeter distance
 * @return distance detected by sonar in centimeters
 */
int sonarScan();

#endif // SONAR_H