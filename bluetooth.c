/**
 * Bluetooth Control API - provides a set of functions for controlling bluetooth communications via USART
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 6/1/2015
 */

// Includes
#include <avr/io.h>

// Prototypes
void init_bluetooth(unsigned long baud);
void serial_putc(char data);
void serial_puts(char x[]);
char serial_getc();

/// Initialize Bluetooth Transmission
/**
 * Initialization function used to setup USART registers for bluetooth communication
 * @param baud opcode representing the baud rate to be used for serial communication
 */
void init_bluetooth(unsigned long baud)
{
	UBRR0H = (unsigned char)(baud >> 8);    // set baud to inserted parameter
	UBRR0L = (unsigned char)(baud);			// set baud to inserted parameter
	UCSR0A = 0b00000010;                    // enable double transmission speeds
	UCSR0C = 0b00001110;                    // 8 bit data frame and 2 bit stop
	UCSR0B = 0b00011000;                    // enable transmition and reception
}

/// Transmit a Single Character
/**
 * Trasmition function used to send a single 8 bit character via bluetooth
 * @param data the 8 bit character to be sent
 */
void serial_putc(char data)
{
	while((UCSR0A & 0b00100000) == 0);      // while previous transmition is not complete
	UDR0 = data;                            // place data value in transmition register
}

/// Transmit a Formatted String
/**
 * Trasmition function used to send a string of 8 bit characters via bluetooth
 * @param string of 8 bit characters to be sent
 */
void serial_puts(char x[])
{
    int i;
	for(i = 0; i < strlen(x); i++)          // for each character in the string
	{
		serial_putc(x[i]);                  // send that character using seriel_putc
	}
}

/// Receive a Single Character
/**
 * Reception function used to receive a single 8 bit character via bluetooth
 * @return the 8 bit character received
 */
char serial_getc()
{
	while((UCSR0A & 0b10000000) == 0);      // while reception is not complete
	return UDR0;                            // return the received character
}