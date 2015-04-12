#ifndef SCAN_H
#define SCAN_H

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include "util.h"
#include "lcd.h"
#include "sonar.h"
#include "ir.h"
#include "servo.h"
#include "bluetooth.h"

/**
 * Scanning Control API Header - Provides a set of functions for controlling sensor scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Scans Environment and Returns
void fullScan();

/// Scan with IR and Sonar and Store Result to Arrays at Appropriate Angle
void sensorScan(int k, int irDistance[], int sonarDistance[]);

/// Analyzes Scan Data and Manages Object Array
void objectHandler(int k, int irDistance[], int sonarDistance[], struct object objects[], int* numObjects);

/// Converts Angular Width to Actual Width
float angularToCm(struct object ob, int distance);

#endif // SCAN_H