/**
 * Servo Control API Header - provides a set of functions for controlling servo positioning
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/21/2015
 */

// Includes
#include <avr/io.h>

#ifndef SERVO_H
#define SERVO_H

/// Initialize Servo Motor
/**
 * Initialization function for configuring servo control registers
 */
void init_servo();

/// Move Servo to Given Degree
/**
 * Position the servo at the given degree as a fixed scale relative to the VORTEX platform
 * @param degrees fixed degree to which the servo will be moved
 */
void moveServo(int degrees);

#endif // SERVO_H