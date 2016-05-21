/**
 * Scanning Control API Header - Provides a set of functions for controlling sensor scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef SCAN_H
#define SCAN_H

// Includes
#include <avr/io.h>
#include <math.h>
#include "util.h"
#include "lcd.h"
#include "sonar.h"
#include "ir.h"
#include "servo.h"
#include "bluetooth.h"

/// Scans Environment
/**
 * Scans the surrounding environment and transmits information about objects found
 */
void fullScan();

/// Scan with IR and Sonar and Store Result to Arrays at Appropriate Angle
/**
 * Triggers ir and sonar pulses and recordes data at appropriate indeces in the cooresponding arrays
 * @param k the angle at which the servo is currently positioned
 * @param irDistance array in which to store distances from ir scans
 * @param sonarDistance array in which to store distances from sonar scan
 */
void sensorScan(int k, int irDistance[], int sonarDistance[]);

/// Analyzes Scan Data and Manages Object Array
/**
 * Analyzes scan data for each pulse and manages obect array information using enum and struct earlier defined
 * @param k the angel at which the servo is currently positioned
 * @param irDistance array for storing ir distances
 * @param sonarDistance array for storing sonar distances
 * @param ob array for storing object structs as detected
 * @param numObjects stores the current number of objects detected
 * @param irStatus enum describing current scan status
 */
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects, enum status* irStatus);

/// Converts Angular Width to Actual Width
/**
 * Converts the angular size of the given object into the actual wicth in centimeters using the midangle distance
 * @param ob the object struct to be converted
 * @param distance the distance to the object at its midangle
 * @return the actual width of the object
 */
float angularToCm(myob ob, int distance);

#endif // SCAN_H