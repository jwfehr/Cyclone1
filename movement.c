#include <avr/io.h>
#include <stdlib.h>
#include "open_interface.h"
#include "music.h"
#include "LED.h"
#include "bluetooth.h"

//ROBOT #6

/**
 * Vortex Movement Control API - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/18/2015
 */

int fullSpeed = 200;			//Speed that robot will travel forwards or backwards in mm/s
int turnSpeed = 100;			//Speed that robot will turn clockwise or counter-clockwise in mm/s
int reverseDistance = 2;		//Distance robot will travel backwards when an object or cliff is encountered in cm
int forwardDistance = 25;		//UNUSED: LEFT FROM PREVIOUS CODE

//Calibrate all variables below with each robot(ROBOT 6)
int fl_white_low = 600;
int fl_white_high = 800;
int fr_white_low = 800;
int fr_white_high = 1050;
int l_white_low = 1200;
int l_white_high = 1500;
int r_white_low = 450;
int r_white_high = 700;

int fl_green_low = 1000;
int fl_green_high = 1200;
int fr_green_low = 1350;
int fr_green_high = 1600;
int l_green_low = 1850;
int l_green_high = 2150;
int r_green_low = 800;
int r_green_high = 1000;


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
	
	while (sum < centimeters * 10) {								//While robot has not travelled specified distance 
		oi_update(sensor);											//Update sensor data
		sum += sensor->distance;									//Add distance travelled since last sensor update to sum
		if(sensor->bumper_left)										//IF left bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rLEFT BUMP SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			play_damage();									
			break;													//Break loop
		}
		if(sensor->bumper_right)									//IF right bump sensor is activated
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rRIGHT BUMP SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			play_damage();
			break;													//Break loop
		}
		if(sensor->cliff_left)		//IF left cliff sensor is activated when not activated by yellow tape
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rLEFT CLIFF SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_frontleft)			//IF front left cliff sensor is activated when not activated by yellow tape
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rFRONT LEFT CLIFF SENSOR ACTIVATED\n\r";		//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_frontright)		//IF front right cliff sensor is activated when not activated by yellow tape
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rFRONT RIGHT CLIFF SENSOR ACTIVATED\n\r";	//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if(sensor->cliff_right)		//IF right bump sensor is activated when not activated by yellow tape
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rRIGHT CLIFF SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;													//Break loop
		}
		if (sensor->cliff_frontleft_signal >= fl_white_low && sensor->cliff_frontleft_signal <= fl_white_high) 
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rFRONT LEFT CLIFF EDGE SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;
		}
		if (sensor->cliff_left_signal >= l_white_low && sensor->cliff_left_signal <= l_white_high)
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rLEFT CLIFF EDGE SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;
		}
		if (sensor->cliff_frontright_signal >= fr_white_low && sensor->cliff_frontright_signal <= fr_white_high)
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rFRONT RIGHT CLIFF EDGE SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;
		}
		if (sensor->cliff_right_signal >= r_white_low && sensor->cliff_right_signal <= r_white_high)
		{
			moveBackward(sensor, reverseDistance);					//Move robot backwards set reverse distance
			sum -= reverseDistance * 10;							//Subtract reverse distance from sum
			char str[] = "\n\rRIGHT CLIFF EDGE SENSOR ACTIVATED\n\r";			//Create string to notify of sensor activation
			serial_puts(str);										//Transmit str to Putty
			break;
		}
		if (sensor->cliff_frontleft_signal >= fl_green_low && sensor->cliff_frontleft_signal <= fl_green_high)
		{
			finish_retrieval(sensor);
			break;
		}
		if (sensor->cliff_frontright_signal >= fr_green_low && sensor->cliff_frontright_signal <= fr_green_high)
		{
			finish_retrieval(sensor);
			break;
		}
		if (sensor->cliff_left_signal >= l_green_low && sensor->cliff_left_signal <= l_green_high)
		{
			finish_retrieval(sensor);
			break;
		}
		if (sensor->cliff_right_signal >= r_green_low && sensor->cliff_right_signal <= r_green_high)
		{
			finish_retrieval(sensor);
			break;
		}
		oi_set_wheels(fullSpeed, fullSpeed);							//Sets wheels to earlier specified speed
	}
	oi_set_wheels(0, 0);												//Stop Robot
	char distance_str[100];												//Create string to write distance travelled
	sprintf(distance_str, "\nNet Distance Moved: %d cm\n\r", (sum / 10));	//Writes "Net Distance Moved: sum" to distance_str
	serial_puts(distance_str);											//Transmits distance_str to Putty
}

///Begins an automated finish sequence to position the robot in the retrieval zone
/**
 *First, the robot moves forward 15 centimeters to position self fully in retrieval zone
 *Second, the robot plays the flag sound from the Mario games, signaling it is in final zone
 *Third, the robot notifies the controller of location and that it is entering standby mode
 *Lastly, the robot enters standby mode by being placed into an infinite loop of altering LEDs to signify end
 */
void finish_retrieval(oi_t*sensor) {
	moveForward(sensor,15);
	oi_set_wheels(0,0);
	play_flag();
	char str[] = "IN RETRIEVAL ZONE: ENTERING STANDBY MODE\n\r";
	serial_puts(str);
	final_LED_sequence();
}

void finish_without_move(oi_t*sensor) {
	oi_set_wheels(0,0);
	play_flag();
	char str[] = "IN RETRIEVAL ZONE: ENTERING STANDBY MODE\n\r";
	serial_puts(str);
	final_LED_sequence();
}