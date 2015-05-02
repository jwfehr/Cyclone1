/**
 * Initialization Function Header - A single function that calls the init functions for all necessary components
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

#ifndef INIT_H
#define INIT_H

// Includes
#include <avr/io.h>
#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"

/// Initialize Function
/**
 * Calls the functions to initialize all necessary functions
 * @param self block of allocated memory for open interfacd
 */
void initAll(oi_t *self);

#endif // INIT_H