/**
 *  UI.c/Users/mitchell/GitHub/CPRE288 Final.c/UI.h
 
 *  @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach
      Bennett
 *  @date 4/12/15.
 
 */

#include "UI.h"
#include "bluetooth.h"
#include "movement.h"

/// Read user input character by character and store in char array
/// user_input_string
void
read_raw_UI()
{
    int cur_char;
    int i;
    
    cur_char = serial_getc();
    serial_putc(cur_char);
    
    while (cur_char != 13) {
        user_input_string[i] = cur_char;
        cur_char = serial_getc();
        serial_putc(cur_char);
        i++;
    }
}

/// Display HELP information
void
display_help()
{
    serial_puts("Press 'h' at any time to view a list of "
                "possible commands.\n\r\n\r");
    serial_puts("f_'int' = Move Forward 'int' centimeters/n/r");
    serial_puts("b_'int' = Move Backward 'int' centimeters/n/r");
    serial_puts("l_'int' = Turn Left 'int' degrees/n/r");
    serial_puts("r_'int' = Turn Right 'int' degrees/n/r");
    serial_puts("s = Scan 180 degrees/n/r");
}

/// Read string of user input
void
read_user_input_string()
{
    char command;
    int specifier;
    
    
    
    command = user_input_string[0];
    
    // If an integer specifier is present, read and put into 'specifier'
    if (user_input_string[1] == '_') {
        
        int i;
        int array_size;
        
        // Length of user_input_string
        array_size = (sizeof(user_input_string)/sizeof(char));
        char spec[array_size - 2 /*Ignore first two indices*/];
        i = 2; /*Start scanning user_input_string after first two indices*/
        
        while (user_input_string[i] != '\0') {
            spec[i-2] = user_input_string[i]
            i++;
        }

        sscanf(spec, '%d', &specifier);
    }
    
    
    /*
     * Check type of command being issued
     *
     * f = Foreward
     * b = Backward
     * l = Turn Left
     * r = Turn Right
     * s = Scan
     * h = HELP
     *
     */
    switch (command) {
            
            case 'f':
            moveForward(/*TODO: oi_t*sensor*/, specifier);
            break;
            
            case 'b':
            moveBackward(/*TODO: oi_t*sensor*/, specifier);
            break;
            
            case 'l':
            turnCounterClockwise(/*TODO: oi_t*sensor*/, specifier);
            break;
            
            case 'r':
            turnClockwise(/*TODO: oi_t*sensor*/, specifier);
            break;
            
            case 's':
            //TODO: Call scan function
            break;
            
            case 'h':
            display_help();
            break;
    }
}