#include "open_interface.h"

/**
 * Vortex Movement Control API - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

int fullSpeed = 300;
int turnSpeed = 100;
int reverseDistance = 15;
int forwardDistance = 25;

/// Move Forwards Given Number of Centimeters
void moveForward(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(fullSpeed, fullSpeed);
	while (sum < centimeters * 10)
	{
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0);
}

/// Move Backwards Given Number of Centimeteres
void moveBackward(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(-1*fullSpeed, -1*fullSpeed);
	while (sum < centimeters * 10)
    {
		oi_update(sensor);
		sum -= sensor->distance;
	}
	oi_set_wheels(0, 0);
}

/// Turn Clockwise Given Number of Degrees
void turnClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;
	oi_set_wheels(-1*turnSpeed, turnSpeed);
	while (sum < degrees)
	{
		oi_update(sensor);
		sum -= sensor->angle;
	}
	oi_set_wheels(0, 0);
}

/// Turn Counter-Clockwise Given Number of Degrees
void turnCounterClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;
	oi_set_wheels(turnSpeed, -1*turnSpeed);
	while (sum < degrees)
	{
		oi_update(sensor);
		sum += sensor->angle;
	}
	oi_set_wheels(0, 0);
}

/// Move Forwards Given Number of Centimeters with Bump Detection Activated
void moveForwardWithBumper(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(fullSpeed, fullSpeed);
	while (sum < centimeters * 10) {
		oi_update(sensor);
		sum += sensor->distance;
		if(sensor->bumper_left)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			turnClockwise(sensor, 90);
			moveForward(sensor, forwardDistance);
			turnCounterClockwise(sensor, 90);
		}
		if(sensor->bumper_right)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			turnCounterClockwise(sensor, 90);
			moveForward(sensor, forwardDistance);
			turnClockwise(sensor, 90);
		}
	oi_set_wheels(fullSpeed, fullSpeed);
	}
	oi_set_wheels(0, 0);
}