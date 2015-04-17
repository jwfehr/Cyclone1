#include <stdio.h>
#include "open_interface.h"
#include "bluetooth.h"
#include <avr/io.h>

/**
 * Vortex Movement Control API - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

int fullSpeed = 200;
int turnSpeed = 100;
int reverseDistance = 2;
int forwardDistance = 25;

/// Move Forwards Given Number of Centimeters
/**
 *Moves the robot a given number of centimeters forwards
 *@param oi_t*sensor the sensor set to be used
 *@param centimeters an integer value of the number of centimeters to move the robot
 */
void moveForward(oi_t *sensor, int centimeters)
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
/**
 *Moves the robot a given number of centimeters backwards
 *@param oi_t*sensor the sensor set to be used
 *@param centimeters an integer value of the number of centimeters to move the robot
 */
void moveBackward(oi_t *sensor, int centimeters)
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
/**
 * Rotates the robot a given number of degrees clockwise
 *@param oi_t*sensor the sensor set to be used
 *@param degrees an integer value of the number of degrees to rotate the robot
 */
void turnClockwise(oi_t *sensor, int degrees)
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
/**
 * Rotates the robot a given number of degrees counter-clockwise
 *@param oi_t*sensor the sensor set to be used
 *@param degrees an integer value of the number of degrees to rotate the robot
 */
void turnCounterClockwise(oi_t *sensor, int degrees)
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

/// Move Forwards Given Number of Centimeters with Sensors Activated
/**
 *Moves the robot forward a given number of centimeters with bump and cliff sensors active.
 *If sensors are activated the robot will stop, back up 2 cm and notify the controller of the sensor status, as well the net distance the robot travelled.
 *
 *@param oi_t*sensor the sensor set to be used
 *@param centimeters an positive integer value indicating how far the robot is to move
 *
 */
void moveForwardWithSensors(oi_t *sensor, int centimeters)
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
			char str[] = "\nLEFT BUMP SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
		if(sensor->bumper_right)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			char str[] = "\nRIGHT BUMP SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
		if(sensor->cliff_left)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			char str[] = "\nLEFT CLIFF SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
		if(sensor->cliff_frontleft)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			char str[] = "\nFRONT LEFT CLIFF SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
		if(sensor->cliff_frontright)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			char str[] = "\nFRONT RIGHT CLIFF SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
		if(sensor->cliff_right)
		{
			moveBackward(sensor, reverseDistance);
			sum -= reverseDistance * 10;
			char str[] = "\nRIGHT CLIFF SENSOR ACTIVATED\r\n";
			serial_puts(str);
			break;
		}
	}
	oi_set_wheels(0, 0);
	char distance_str[100];
	sprintf(distance_str, "\nNet Distance Moved: %d cm\r\n", (sum / 10));
	serial_puts(distance_str);
}