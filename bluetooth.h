/**
 * Bluetooth Control API - provides a set of functions for controlling bluetooth communications via USART
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/13/2015
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/// Initialize Bluetooth Transmission
/**
 * Initilization function used to setup USART registers for bluetooth communication
 * @param baud opcode representing the baudrate to be used for serial communication
 */
void init_bluetooth(unsigned long baud);

/// Transmit a Single Character
/**
 * Trasmition function used to send a single 8 bit character via bluetooth
 * @param data the 8 bit character to be sent
 */
void serial_putc(char data);

/// Transmit a Formatted String
/**
 * Trasmition function used to send a string of 8 bit characters via bluetooth
 * @param string of 8 bit characters to be sent
 */
void serial_puts(char x[]);

/// Receive a Single Character
/**
 * Reception function used to recieve a single 8 bit character via bluetooth
 * @return the 8 bit character recieved
 */
char serial_getc();

#endif // BLUETOOTH_H