#ifndef SERVO_H
#define SERVO_H

/**
 * Servo Contorl API - Provides a set of functions for controlling servo positioning
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Initialize Servo Motor
void init_servo();

/// Move Servo to Given Degree
void moveServo(int degrees);

#endif // SERVO_H