#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "open_interface.h"
/**
 * Vortex Movement Control API Header - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

/// Move Forwards Given Number of Centimeters
void moveForward(oi_t *sensor, int centimeters);

/// Move Backwards Given Number of Centimeteres
void moveBackward(oi_t *sensor, int centimeters);

/// Turn Clockwise Given Number of Degrees
void turnClockwise(oi_t *sensor, int degrees);

/// Turn Counter-Clockwise Given Number of Degrees
void turnCounterClockwise(oi_t *sensor, int degrees);

/// Move Forwards Given Number of Centimeters with Bump Detection Activated
void moveForwardWithSensors(oi_t* sensor, int centimeters);

#endif // MOVEMENT_H