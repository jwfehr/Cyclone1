/**
 * Vortex Movement Control API - Provides a set of function for controlling the movement of the Vortex platform
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include "open_interface.h"
#include "music.h"
#include "led.h"
#include "bluetooth.h"

// Prototypes
void moveForward(oi_t* sensor, int centimeters);
void moveBackward(oi_t* sensor, int centimeters);
void turnClockwise(oi_t* sensor, int degrees);
void turnCounterClockwise(oi_t* sensor, int degrees);
void moveForwardWithSensors(oi_t* sensor, int centimeters);
void finish_retrieval(oi_t* sensor);
void finish_without_move(oi_t* sensor);

// Global Variables
int fullSpeed = 200;			// speed that robot will travel forwards or backwards in mm/s
int turnSpeed = 100;			// speed that robot will turn clockwise or counter-clockwise in mm/s
int reverseDistance = 2;		// distance robot will travel backwards when an object or cliff is encountered in cm
int fl_white_low = 600;         // front left sensor white numbers
int fl_white_high = 800;
int fr_white_low = 800;         // front right sensor white numbers
int fr_white_high = 1050;
int l_white_low = 1200;         // left sensor white numbers
int l_white_high = 1500;
int r_white_low = 450;          // right sensor white numbers
int r_white_high = 700;
int fl_green_low = 1000;        // front left sensor green numbers
int fl_green_high = 1200;
int fr_green_low = 1350;        // front right sensor green numbers
int fr_green_high = 1600;
int l_green_low = 1850;         // left sensor green numbers
int l_green_high = 2150;
int r_green_low = 800;          // right sensor green numbers
int r_green_high = 1000;

/// Move Forwards Given Number of Centimeters
/**
 * Moves the robot a given number of centimeters forwards
 * @param sensor the sensor set to be used
 * @param centimeters an integer value of the number of centimeters to move the robot
 */
void moveForward(oi_t* sensor, int centimeters)
{
	int sum = 0;								// keeps track of running total distance traveled
	oi_set_wheels(fullSpeed, fullSpeed);		// set wheels to forward speed
	while (sum < centimeters * 10)				// while more distance to cover
	{
		oi_update(sensor);						// update sensor data
		sum += sensor->distance;				// add distance travelled since last sensor update to sum
	}
	oi_set_wheels(0, 0);						// stop robot when distance has been covered
}

/// Move Backwards Given Number of Centimeteres
/**
 * Moves the robot a given number of centimeters backwards
 * @param sensor the sensor set to be used
 * @param centimeters an integer value of the number of centimeters to move the robot
 */
void moveBackward(oi_t* sensor, int centimeters)
{
	int sum = 0;								// keeps track of running total distance traveled
	oi_set_wheels(-1*fullSpeed, -1*fullSpeed);	// set wheels to reverse sepeed using negatives
	while (sum < centimeters * 10)				// while more distance to cover
    {
		oi_update(sensor);						// update sensor data
		sum -= sensor->distance;				// subtract distance travelled since last sensor update to sum
	}
	oi_set_wheels(0, 0);						// stop robot when distance has been covered
}

/// Turn Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees clockwise
 * @param sensor the sensor set to be used
 * @param degrees an integer value of the number of degrees to rotate the robot
 */
void turnClockwise(oi_t* sensor, int degrees)
{
	int sum = 0;								// keeps track of runnig total degrees rotated
	oi_set_wheels(-1*turnSpeed, turnSpeed);		// set wheels to turn speed
	while (sum < degrees)						// while more degrees to turn
	{
		oi_update(sensor);						// update sensor data
		sum -= sensor->angle;					// subtract degrees turned since last sensor update to sum
	}
	oi_set_wheels(0, 0);						// stop robot when degrees have been turned
}

/// Turn Counter-Clockwise Given Number of Degrees
/**
 * Rotates the robot a given number of degrees counter-clockwise
 * @param sensor the sensor set to be used
 * @param degrees an integer value of the number of degrees to rotate the robot
 */
void turnCounterClockwise(oi_t* sensor, int degrees)
{
	int sum = 0;								// keeps track of running total degress rotated
	oi_set_wheels(turnSpeed, -1*turnSpeed);		// set wheels to turn speed
	while (sum < degrees)						// while more degrees to turn
	{
		oi_update(sensor);						// update sensor data
		sum += sensor->angle;					// add degrees turned since last sensor update to sum
	}
	oi_set_wheels(0, 0);						// stop robot when degrees have been turned
}

/// Move Forwards Given Number of Centimeters with Sensors Activated
/**
 * Moves the robot forward a given number of centimeters with bump and cliff sensors active.
 * If sensors are activated the robot will stop, back up 2 cm and notify the controller of the sensor status, 
 * as well the net distance the robot travelled.
 * @param sensor the sensor set to be used
 * @param centimeters an positive integer value indicating how far the robot is to move
 */
void moveForwardWithSensors(oi_t* sensor, int centimeters)
{
	int sum = 0;													// value to keep track of total distance travelled
	while (sum < centimeters * 10) {								// while robot has not travelled specified distance
		oi_update(sensor);											// update sensor data
		sum += sensor->distance;									// add distance travelled since last sensor update to sum
		if(sensor->bumper_left)
		{                                                           // if left bump sensor is activated
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rLEFT BUMP SENSOR ACTIVATED\n\r";		// create string to notify of sensor activation
			serial_puts(str);										// transmit string
			play_damage();                                          // play damage sound
			break;
		}
		if(sensor->bumper_right)
		{                                                           // if right bump sensor is activated
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rRIGHT BUMP SENSOR ACTIVATED\n\r";		// create string to notify of sensor activation
			serial_puts(str);										// transmit string
			play_damage();                                          // play damage sound
			break;
		}
		if(sensor->cliff_left)
		{                                                           // if left cliff sensor is activated when not activated by yellow tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rLEFT CLIFF SENSOR ACTIVATED\n\r";     // ceate string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if(sensor->cliff_frontleft)
		{                                                           // if front left cliff sensor is activated when not activated by yellow tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[]="\n\rFRONT LEFT CLIFF SENSOR ACTIVATED\n\r"; // create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if(sensor->cliff_frontright)
		{                                                           // if front right cliff sensor is activated when not activated by yellow tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[]="\n\rFRONT RIGHT CLIFF SENSOR ACTIVATED\n\r";// create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if(sensor->cliff_right)
		{                                                           // if right bump sensor is activated when not activated by yellow tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rRIGHT CLIFF SENSOR ACTIVATED\n\r";    // create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if (sensor->cliff_frontleft_signal >= fl_white_low && sensor->cliff_frontleft_signal <= fl_white_high) 
		{                                                           // if front left sensor encouters white tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[]="\n\rFRONT LEFT CLIFF EDGE SENSOR ACTIVATED\n\r"; // create string to notify of sensor activation
			serial_puts(str);										// transtmit string
			break;
		}
		if (sensor->cliff_left_signal >= l_white_low && sensor->cliff_left_signal <= l_white_high)
		{                                                           // if left sensor encounteres white tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rLEFT CLIFF EDGE SENSOR ACTIVATED\n\r";// create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if (sensor->cliff_frontright_signal >= fr_white_low && sensor->cliff_frontright_signal <= fr_white_high)
		{                                                           // if front right sensor encounters white tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[] = "\n\rFRONT RIGHT CLIFF EDGE SENSOR ACTIVATED\n\r"; // create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if (sensor->cliff_right_signal >= r_white_low && sensor->cliff_right_signal <= r_white_high)
		{                                                           // if right sensor encounteres white tape
			moveBackward(sensor, reverseDistance);					// move robot backwards set reverse distance
			sum -= reverseDistance * 10;							// subtract reverse distance from sum
			char str[]="\n\rRIGHT CLIFF EDGE SENSOR ACTIVATED\n\r"; // create string to notify of sensor activation
			serial_puts(str);										// transmit string
			break;
		}
		if (sensor->cliff_frontleft_signal >= fl_green_low && sensor->cliff_frontleft_signal <= fl_green_high)
		{                                                           // if green is detected
			finish_retrieval(sensor);                               // trigger finish
			break;
		}
		if (sensor->cliff_frontright_signal >= fr_green_low && sensor->cliff_frontright_signal <= fr_green_high)
		{                                                           // if green is detected
			finish_retrieval(sensor);                               // trigger finish
			break;
		}
		if (sensor->cliff_left_signal >= l_green_low && sensor->cliff_left_signal <= l_green_high)
		{                                                           // if green is detected
			finish_retrieval(sensor);                               // trigger finish
			break;
		}
		if (sensor->cliff_right_signal >= r_green_low && sensor->cliff_right_signal <= r_green_high)
		{                                                           // if green is detected
			finish_retrieval(sensor);                               // trigger finish
			break;
		}
		oi_set_wheels(fullSpeed, fullSpeed);                        // set wheels to earlier specified speed
	}
	oi_set_wheels(0, 0);                                                    // stop robot
	char distance_str[100];                                                 // create net distance string
	sprintf(distance_str, "\nNet Distance Moved: %d cm\n\r", (sum / 10));	// writes net distance string
	serial_puts(distance_str);                                              // transmits net distance string
}

/// Begins an Automated Finish Sequence to Position the Robot in the Retrieval Zone with Movement
/**
 * Triggers the final sequqncy of events when approaching the goal zone with forward movement
 * @param sensor the sensor set to be used
 */
void finish_retrieval(oi_t* sensor)
{
	moveForward(sensor,15);                                         // move forward 15 centimeters
	oi_set_wheels(0,0);                                             // stop the robot
	play_flag();                                                    // play final song
	char str[] = "IN RETRIEVAL ZONE: ENTERING STANDBY MODE\n\r";    // create message string
	serial_puts(str);                                               // transmit message string
	final_LED_sequence();                                           // trigger LED finish sequence
}

/// Begins an Automated Finish Sequence to Position the Robot in the Retrieval Zone without Movement
/**
 * Triggers the final sequqncy of events when approaching the goal zone with out forward movement
 * @param sensor the sensor set to be used
 */
void finish_without_move(oi_t* sensor)
{
	oi_set_wheels(0,0);                                             // stop the robot
	play_flag();                                                    // play final song
	char str[] = "IN RETRIEVAL ZONE: ENTERING STANDBY MODE\n\r";    // create message string
	serial_puts(str);                                               // transmit message string
	final_LED_sequence();                                           // trigger LED finish sequence
}