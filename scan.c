#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include "util.h"
#include "lcd.h"
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

/// Scans Environment and Returns
void fullScan()
{
	int irDistance[91] = {0};
	int sonarDistance[91] = {0};
	myob objects[10];
	int numObjects = 0;
	char str[100];
	
	// printing stuff - can remove				
	sprintf(str, "Degrees\tIR Distance (cm)\tSonar Distance\n\r");
	serial_puts(str);
	
    int i;
	for(i = 0; i <= 180; i += 2)
	{
		moveServo(i);
		wait_ms(100); // try to reduce
		sensorScan(i, irDistance, sonarDistance);
		objectHandler(i, irDistance, sonarDistance, objects, &numObjects);
//      printing stuff
		sprintf(str, "%d\t%d\n\r", i, irDistance[i/2], sonarDistance[i/2]);
		serial_puts(str);
	}
	
	int minObject = 0;
	float minValue = 10000.0;
	float value = 0.0;
	
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
		
		value = angularTocm(objects[j], distance);
		if(value < minValue)
		{
			minObject = j;
			minValue = value;
		}
	}

//  printing stuff
	lprintf("NUM OBJECTS: %d, INDEX: %d ", numObjects, minObject+1);
	moveServo((objects[minObject].startAngle + objects[minObject].endAngle)/2);
}

/// Scan with IR and Sonar and Store Result to Arrays at Appropriate Angle
void sensorScan(int k, int irDistance[], int sonarDistance[])
{
	k = k/2;
	sonarDistance[k] = sonarScan();
	irDistance[k] = irScan();
}

/// Analyzes Scan Data and Manages Object Array
void objectHandler(int k, int irDistance[], int sonarDistance[], myob ob[], int* numObjects)
{
	static enum status irStatus = noObject;
	static enum status sonarStatus = noObject;

    if((irStatus == noObject) && (irDistance[k/2] > 80) && (sonarStatus == noObject) && (sonarDistance[k/2] > 80)){} // if both had no object and both still beyond 80
	else if((irStatus == noObject) && (irDistance[k/2] <= 80) && (sonarStatus == noObject) && (sonarDistance[k/2] <= 80)) // if both had no object and both less than 80
	{
		irStatus = hasObject;
        sonarStatus = hasObject;
		ob[*numObjects].startAngle = k;
		ob[*numObjects].startDistance = irDistance[k/2];
	}
	else if((irStatus == hasObject) && (irDistance[k/2] <= 80) && (sonarStatus == hasObject) && (sonarDistance[k/2] <= 80)) // if both have object and are still less than 80
	{
		ob[*numObjects].endAngle = k;
		ob[*numObjects].endDistance = irDistance[k/2];
	}
	else if((irStatus == hasObject) && (irDistance[k/2] > 80) && (sonarStatus == hasObject) && (sonarDistance[k/2] > 80)) // if both have object and both now greater than 80
	{
		irStatus = noObject;
        sonarStatus = noObject;
		(*numObjects)++;
	}
}

/// Converts Angular Width to Actual Width
float angularToCm(myob ob, int distance)
{
	return (2*distance*tan(((ob.endAngle - ob.startAngle)/2)* 3.1415/180.0));
}