/** 
 * Bluetooth Control API Header - Provides a set of function headers for controlling bluetooth functions 
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 06/26/2012
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/// Initialize Bluetooth Transmission
void init_bluetooth(unsigned long baud);

/// Transmit a Single Character
void serial_putc(char data);

/// Transmit a Formatted String
void serial_puts(char x[]);

/// Receive a Single Character
char serial_getc();

#endif // BLUETOOTH_H