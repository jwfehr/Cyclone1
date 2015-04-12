#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"

char command = 'n';

int main(int argc)
{
  //TODO START INTERFACE, PRINT STARTING INTERFACE

  while(command != 's') //Wait for Start Command
  {
    command = serial_getc();
  }

  //START TRAVERSING CODE

  while("NOT DONE") //While the robot is not in the Final Zone
  {
    //TODO Interface and Movement
  }

  //TODO FLASH LEDS WHEN DONE


}
