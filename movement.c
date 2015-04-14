#include "open_interface.h"
#include "bluetooth.h"

/**
 * Vortex Movement Control API - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

int fullSpeed = 300;			//Speed that robot will travel forwards or backwards in mm/s
int turnSpeed = 100;			//Speed that robot will turn clockwise or counter-clockwise in mm/s
int reverseDistance = 2;		//Distance robot will travel backwards when an object or cliff is encountered in cm
int forwardDistance = 25;		//UNUSED: LEFT FROM PREVIOUS CODE

/// Move Forwards Given Number of Centimeters
/**
 *Moves the robot a given number of centimeters forwards
 *@param oi_t*sensor the sensor set to be used
 *@param centimeters an integer value of the number of centimeters to move the robot
 */
void moveForward(oi_t*sensor, int centimeters)
{
	int sum = 0;								//Int value to keep track of total distance travelled
	oi_set_wheels(fullSpeed, fullSpeed);		//Set wheels to earlier specified speed
	while (sum < centimeters * 10)				//While robot has not moved distance given	
	{
		oi_update(sensor);						//Update sensor data
		sum += sensor->distance;				//Adds distance travelled since last sensor update to sum
	}
	oi_set_wheels(0, 0);						//Stops Robot
}

/// Move Backwards Given Number of Centimeteres
/**
 *Moves the robot a given number of centimeters backwards
 *@param oi_t*sensor the sensor set to be used
 *@param centimeters an integer value of the number of centimeters to move the robot
 */
void moveBackward(oi_t*sensor, int centimeters)
{
	int sum = 0;								//Int value to keep track of total distance travelled
	oi_set_wheels(-1*fullSpeed, -1*fullSpeed);	//Set wheels to negative earlier specified speed
	while (sum < centimeters * 10)				//While robot has not moved distance given	
    {
		oi_update(sensor);						//Update sensor data
		sum -= sensor->distance;				//Subtracts distance travelled since last sensor update to sum
	}
	oi_set_wheels(0, 0);						//Stops Robot
}

/// Turn Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees clockwise
 *@param oi_t*sensor the sensor set to be used
 *@param degrees an integer value of the number of degrees to rotate the robot
 */
void turnClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;								//Int value to keep track of total degreed rotated
	oi_set_wheels(-1*turnSpeed, turnSpeed);		//Sets wheels to turn speed counter-clockwise
	while (sum < degrees)						//While robot has not turned degreed given
	{
		oi_update(sensor);						//Update sensor data
		sum -= sensor->angle;					//Subtracts degrees turned since last sensor update to sum
	}
	oi_set_wheels(0, 0);						//Stops Robot
}

/// Turn Counter-Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees counter-clockwise
 *@param oi_t*sensor the sensor set to be used
 *@param degrees an integer value of the number of degrees to rotate the robot
 */
void turnCounterClockwise(oi_t*sensor, int degrees)
{
	int sum = 0;								//Int value to keep track of total degreed rotated
	oi_set_wheels(turnSpeed, -1*turnSpeed);		//Sets wheels to turn speed clockwise
	while (sum < degrees)						//While robot has not turned degreed given
	{
		oi_update(sensor);						//Update sensor data
		sum += sensor->angle;					//Adds degrees turned since last sensor update to sum
	}
	oi_set_wheels(0, 0);						//Stops Robot
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
void moveForwardWithSensors(oi_t*sensor, int centimeters)
{
	int sum = 0;													//Int value to keep track of total distance travelled
	oi_set_wheels(fullSpeed, fullSpeed);							//Sets wheels to earlier specified speed
	while (sum < centimeters * 10) {								//While robot has not travelled specified distance 
		oi_update(sensor);											//Update sensor data
		sum += sensor->distance;									//Add distance travelled since last sensor update to sum
		if(sensor->bumper_left)										//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nLEFT BUMP SENSOR ACTIVATED";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->bumper_right)									//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nRIGHT BUMP SENSOR ACTIVATED";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_left)										//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nLEFT CLIFF SENSOR ACTIVATED";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_frontleft)									//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nFRONT LEFT CLIFF SENSOR ACTIVATED";		//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_frontright)								//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nFRONT RIGHT CLIFF SENSOR ACTIVATED";	//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_right)										//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\nRIGHT CLIFF SENSOR ACTIVATED";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
	}
	oi_set_wheels(0, 0);												//Stop Robot
	char distance_str[];												//Create string to write distance travelled
	sprintf(distance_str, "\nNet Distance Moved: %d cm", (sum / 10));	//Writes "Net Distance Moved: sum" to distance_str
	serial_puts(distance_str);											//Transmits distance_str to Putty
}