#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include "util.h"
#include "sonar.h"
#include "ir.h"
#include "servo.h"
#include "bluetooth.h"

/**
 * Scanning Control API - Provides a set of functions for controlling sensor scans
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

typedef struct object
{
	int startAngle;
	int startDistance;
	int endAngle;
	int endDistance;
}myob;

enum status
{
    hasObject,
    noObject,
};

float angularToCm(myob ob, int distance);
void fullScan();
void sensorScan(int k, int irDistance[], int sonarDistance[]);
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects,  enum status* irStatus);

/// Scans Environment and Returns
void fullScan()
{
	int irDistance[91] = {0};
	int sonarDistance[91] = {0};
	myob objects[10];
	int numObjects = 0;
	char str[100];
	static enum status irStatus = noObject;
	
	// printing stuff - can remove				
	//sprintf(str, "Degrees\t\tIR Distance\tSonar Distance\tObject\n\r");
	//serial_puts(str);
	//int jake;
	
	sprintf(str, "Scanning...\n\r");
	serial_puts(str);
	
    int i;
	for(i = 0; i <= 180; i += 2)
	{
		moveServo(i);
		wait_ms(50);
		sensorScan(i, irDistance, sonarDistance);
		objectHandler(i, irDistance, sonarDistance, objects, &numObjects, &irStatus);
		
		// printing stuff - can remove
		//jake = 0;
		//if(irDistance[i/2]<80 && sonarDistance[i/2]<80){ jake = 1111; }
		//sprintf(str, "%d\t\t%d\t\t%d\t\t%d\n\r", i, irDistance[i/2], sonarDistance[i/2], jake);
		//serial_puts(str);
	}
	
    int j;
	for(j = 0; j < numObjects; j++)
	{
		int midAngle = (objects[j].startAngle + objects[j].endAngle)/2;
		int distance;
		if(midAngle % 2 == 0)
		{
			distance = irDistance[midAngle/2];
		}
		else
		{
			distance = (irDistance[(midAngle + 1) / 2] + irDistance[(midAngle - 1) / 2]) / 2;
		}
		float width = angularToCm(objects[j], distance);
		sprintf(str, "Object: %d, Angle: %d, Distance: %d, Width: %f\n\r", j+1, midAngle, distance, width);
		serial_puts(str);
	}
	
	moveServo(0);
	sprintf(str, "Finished Scanning.\n\r");
	serial_puts(str);
}

/// Scan with IR and Sonar and Store Result to Arrays at Appropriate Angle
void sensorScan(int k, int irDistance[], int sonarDistance[])
{
	k = k/2;
	sonarDistance[k] = sonarScan();
	int average = 0;
	average += irScan();
	average += irScan();
	average += irScan();
	average += irScan();
	average += irScan();
	irDistance[k] = average/5;
}

/// Analyzes Scan Data and Manages Object Array
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects, enum status* irStatus)
{
    if((*irStatus == noObject) && (irDistance[k/2] > 80) && (sonarDistance[k/2] > 80)){} // if both had no object and both still beyond 80
	else if((*irStatus == noObject) && (irDistance[k/2] <= 80) && (sonarDistance[k/2] <= 80)) // if both had no object and both less than 80
	{
		*irStatus = hasObject;
		ob[*numObjects].startAngle = k;
		ob[*numObjects].startDistance = sonarDistance[k/2];
	}
	else if((*irStatus == hasObject) && (irDistance[k/2] <= 80) && (sonarDistance[k/2] <= 80)) // if both have object and are still less than 80
	{
		ob[*numObjects].endAngle = k;
		ob[*numObjects].endDistance = sonarDistance[k/2];
	}
	else if((*irStatus == hasObject) && (irDistance[k/2] > 80)) // if both have object and both now greater than 80
	{
		*irStatus = noObject;
		(*numObjects)++;
	}
}

/// Converts Angular Width to Actual Width
float angularToCm(myob ob, int distance)
{
	return (2*distance*tan(((ob.endAngle - ob.startAngle)/2)*(3.14159265/180.0)));
}