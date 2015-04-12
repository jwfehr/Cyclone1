/**
 * Initialization Function - A single function that calls the init functions for all necessary components
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */

#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"

///Initialize Function, Calls the functions to initialize all necessary functions
void initAll(oi_t *self)
{
  init_bluetooth(34);
  init_ir();
  oi_init(self);
  init_servo();
  init_sonar();
}
