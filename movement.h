#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "open_interface.h"

// Move the Robot Forwards a Given Number of Centimeters
void moveForward(oi_t*sensor, int centimeters);

// Move the Robot Backwards a Given Number of Centimeters
void moveBackward(oi_t*sensor, int centimeters);

// Turn the Robot CW in Place Given Number of Degrees
void turnClockwise(oi_t*sensor, int degrees);

// Turn the Robot CCW in Place Given Number of Degrees
void turnCounterClockwise(oi_t*sensor, int degrees);

// Move the Robot Forwards a Given Number of Centimetres with Bumper Sensors Active - reduce the distance travelled backwards
void moveForwardWithBumper(oi_t*sensor, int centimeters);

#endif // MOVEMENT_H