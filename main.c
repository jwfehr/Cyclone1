
#include <avr/io.h>
#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"
#include "init.h"
#include "UI.h"

char command = 'n';
oi_t *sensorData;

int main()
{
    sensorData = oi_alloc();
    initAll(sensorData);
    
    //TODO START INTERFACE, PRINT STARTING INTERFACE
    
    //while(command != 's') //Wait for Start Command
    //{
    //  command = serial_getc();
    //}
    
    //START TRAVERSING CODE
    
    while(1) //While the robot is not in the Final Zone
    {
        //TODO Interface and Movement
        read_user_input_string(sensorData);
        
    }
    
    //TODO FLASH LEDS WHEN DONE
    
    
}
