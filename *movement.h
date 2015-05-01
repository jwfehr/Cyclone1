/**
 * Vortex Movement Control API Header - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

// Includes
#include <avr/io.h>
#include "open_interface.h"
#include "music.h"
#include "LED.h"
#include "bluetooth.h"

/// Move Forwards Given Number of Centimeters
/**
 * Moves the robot a given number of centimeters forwards
 * @param sensor the sensor set to be used
 * @param centimeters an integer value of the number of centimeters to move the robot
 */
void moveForward(oi_t* sensor, int centimeters);

/// Move Backwards Given Number of Centimeteres
/**
 * Moves the robot a given number of centimeters backwards
 * @param sensor the sensor set to be used
 * @param centimeters an integer value of the number of centimeters to move the robot
 */
void moveBackward(oi_t* sensor, int centimeters);

/// Turn Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees clockwise
 * @param sensor the sensor set to be used
 * @param degrees an integer value of the number of degrees to rotate the robot
 */
void turnClockwise(oi_t* sensor, int degrees);

/// Turn Counter-Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees counter-clockwise
 * @param sensor the sensor set to be used
 * @param degrees an integer value of the number of degrees to rotate the robot
 */
void turnCounterClockwise(oi_t* sensor, int degrees);

/// Move Forwards Given Number of Centimeters with Sensors Activated
/**
 * Moves the robot forward a given number of centimeters with bump and cliff sensors active.
 * If sensors are activated the robot will stop, back up 2 cm and notify the controller of the sensor status,
 * as well the net distance the robot travelled.
 * @param sensor the sensor set to be used
 * @param centimeters an positive integer value indicating how far the robot is to move
 */
void moveForwardWithSensors(oi_t* sensor, int centimeters);

/// Begins an Automated Finish Sequence to Position the Robot in the Retrieval Zone with Movement
/**
 * Triggers the final sequqncy of events when approaching the goal zone with forward movement
 * @param sensor the sensor set to be used
 */
void finish_retrieval(oi_t* sensor);

/// Begins an Automated Finish Sequence to Position the Robot in the Retrieval Zone without Movement
/**
 * Triggers the final sequqncy of events when approaching the goal zone with out forward movement
 * @param sensor the sensor set to be used
 */
void finish_without_move(oi_t* sensor);

#endif // MOVEMENT_H