/**
 * Scanning Control API - Provides a set of functions for controlling sensor scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include "util.h"
#include "sonar.h"
#include "ir.h"
#include "servo.h"
#include "bluetooth.h"

// object struct for pillars
typedef struct object
{
	int startAngle;         // angle at which object is first detected
	int startDistance;      // distance to object at first encounter
	int endAngle;           // ange at which object is last detected
	int endDistance;        // distance to object at last encounter
}myob;

// enum defines scan status
enum status
{
    hasObject,      // object currently in scan focus
    noObject,       // no object currently in scan focus
};

// Prototypes
float angularToCm(myob ob, int distance);
void fullScan();
void sensorScan(int k, int irDistance[], int sonarDistance[]);
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects,  enum status* irStatus);

/// Scans Environment
/**
 * Scans the surrounding environment and transmits information about objects found
 */
void fullScan()
{
	int irDistance[91] = {0};                       // array of ir distances for full scan
	int sonarDistance[91] = {0};                    // aray of sonar distances for full scan
	myob objects[10];                               // aray of objects to be detected in scan
	int numObjects = 0;                             // number of objects encuntered in scan
	char str[100];                                  // buffer string for printing
	static enum status irStatus = noObject;         // status enum for ir scanning
	
	sprintf(str, "Scanning...\n\r");                // transmit startup tag
	serial_puts(str);
	
    int i;
	for(i = 0; i <= 180; i += 2)
	{                                                                                   // for full 180 degree scan
		moveServo(i);                                                                   // move servo to degree
		wait_ms(50);                                                                    // wait for servo response
		sensorScan(i, irDistance, sonarDistance);                                       // scan and record distances
		objectHandler(i, irDistance, sonarDistance, objects, &numObjects, &irStatus);   // analyze data and define objects
	}
	
    int j;
	for(j = 0; j < numObjects; j++)
	{                                                                                                           // for each object detected
		int midAngle = (objects[j].startAngle + objects[j].endAngle)/2;                                         // calculate object midangle
		int distance;
		if(midAngle % 2 == 0)                                                                                   // find distance at that midange
		{
			distance = irDistance[midAngle/2];                                                                  // case 1: distance at that angle
		}
		else
		{                                                                                                       // case 2: distance above and beyond midangle
			distance = (irDistance[(midAngle + 1) / 2] + irDistance[(midAngle - 1) / 2]) / 2;
		}
		float width = angularToCm(objects[j], distance);                                                        // caculate acutal width from angular
		sprintf(str, "Object: %d, Angle: %d, Distance: %d, Width: %f\n\r", j+1, midAngle, distance, width);     // transmit object data
		serial_puts(str);
	}
	
	moveServo(0);                               // move servo to intial position for next scan
	sprintf(str, "Finished Scanning.\n\r");     // transmit finished tag
	serial_puts(str);
}

/// Scan with IR and Sonar and Store Result to Arrays at Appropriate Angle
/**
 * Triggers ir and sonar pulses and recordes data at appropriate indeces in the cooresponding arrays
 * @param k the angle at which the servo is currently positioned
 * @param irDistance array in which to store distances from ir scans
 * @param sonarDistance array in which to store distances from sonar scan
 */
void sensorScan(int k, int irDistance[], int sonarDistance[])
{
	k = k/2;                                // convert to indeces form (2 degree angle period)
	sonarDistance[k] = sonarScan();         // store sonar scan result
	int average = 0;
	average += irScan();
	average += irScan();
	average += irScan();
	average += irScan();
	average += irScan();
	irDistance[k] = average/5;              // store average of 5 ir scan results
}

/// Analyzes Scan Data and Manages Object Array
/**
 * Analyzes scan data for each pulse and manages obect array information using enum and struct earlier defined
 * @param k the angel at which the servo is currently positioned
 * @param irDistance array for storing ir distances
 * @param sonarDistance array for storing sonar distances
 * @param ob array for storing object structs as detected
 * @param numObjects stores the current number of objects detected
 * @param irStatus enum describing current scan status
 */
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects, enum status* irStatus)
{
    if((*irStatus == noObject) && (irDistance[k/2] > 80) && (sonarDistance[k/2] > 80)){}        // if both had no object and both still beyond 80
	else if((*irStatus == noObject) && (irDistance[k/2] <= 80) && (sonarDistance[k/2] <= 80))   // if both had no object and both less than 80
	{
		*irStatus = hasObject;                                  // set staus to having object
		ob[*numObjects].startAngle = k;                         // store start angle
		ob[*numObjects].startDistance = sonarDistance[k/2];     // store start distance
	}
	else if((*irStatus == hasObject) && (irDistance[k/2] <= 80) && (sonarDistance[k/2] <= 80))  // if both have object and are still less than 80
	{
		ob[*numObjects].endAngle = k;                           // store end angle
		ob[*numObjects].endDistance = sonarDistance[k/2];       // store end distance
	}
	else if((*irStatus == hasObject) && (irDistance[k/2] > 80))                                 // if both have object and both now greater than 80
	{
		*irStatus = noObject;                                   // set status to not having an object
		(*numObjects)++;                                        // increment number of ojects encountered
	}
}

/// Converts Angular Width to Actual Width
/**
 * Converts the angular size of the given object into the actual wicth in centimeters using the midangle distance
 * @param ob the object struct to be converted
 * @param distance the distance to the object at its midangle
 * @return the actual width of the object
 */
float angularToCm(myob ob, int distance)
{
	return (2*distance*tan(((ob.endAngle - ob.startAngle)/2)*(3.14159265/180.0)));  // basic trig. function for finding width
}