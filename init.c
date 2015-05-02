/**
 * Initialization Function - A single function that calls the init functions for all necessary components
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 5/1/2015
 */

// Includes
#include <avr/io.h>
#include "bluetooth.h"
#include "ir.h"
#include "movement.h"
#include "open_interface.h"
#include "servo.h"
#include "sonar.h"
#include "music.h"

// Prototypes
void initAll(oi_t *self);

/// Initialize Function
/**
 * Calls the functions to initialize all necessary functions
 * @param self block of allocated memory for open interfacd
 */
void initAll(oi_t *self)
{
    init_bluetooth(34);     // initilizes bluetooth using op code for desired baudrate
    init_ir();              // initilizes infrared scanning system
    oi_init(self);          // initilizes open interface struct system
    init_servo();           // initilizes servo control system
    init_sonar();           // initilizes sonar scanning system
    initial_LED();          // initilizes LED control system
}