#include "open_interface.h"

// Move the Robot Forwards a Given Number of Centimeters
void moveForward(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(300, 300);
	while (sum < centimeters * 10)
	{
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0);
}

// Move the Robot Backwards a Given Number of Centimeters
void moveBackward(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(-300, -300); // move forward; full speed
	while (sum < centimeters * 10) {
		oi_update(sensor);
		sum -= sensor->distance;
	}
	oi_set_wheels(0, 0); // stop
}

// Turn the Robot CW in Place Given Number of Degrees
void turnClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;
	oi_set_wheels(-100, 100);
	while (sum < degrees)
	{
		oi_update(sensor);
		sum -= sensor->angle;
	}
	oi_set_wheels(0, 0);
}

// Turn the Robot CCW in Place Given Number of Degrees
void turnCounterClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;
	oi_set_wheels(100, -100);
	while (sum < degrees)
	{
		oi_update(sensor);
		sum += sensor->angle;
	}
	oi_set_wheels(0, 0);
}

// Move the Robot Forwards a Given Number of Centimetres with Bumper Sensors Active
// Reduce the distance travelled backwards
void moveForwardWithBumper(oi_t*sensor, int centimeters)
{
	int sum = 0;
	oi_set_wheels(300, 300);
	while (sum < centimeters * 10) {
		oi_update(sensor);
		sum += sensor->distance;
		if(sensor->bumper_left)
		{
			moveBackward(sensor, 15);
			sum -=150;
			turnClockwise(sensor, 90);
			moveForward(sensor, 25);
			turnCounterClockwise(sensor, 90);
		}
		if(sensor->bumper_right)
		{
			moveBackward(sensor, 15);
			sum -=150;
			turnCounterClockwise(sensor, 90);
			moveForward(sensor, 25);
			turnClockwise(sensor, 90);
		}
	oi_set_wheels(300, 300);
	}
	oi_set_wheels(0, 0);
}