/**
 * Bluetooth Control API - Provides a set of functions for controlling bluetooth communications
 * @author Jacob Johnson, Justin Fehr, Mitchell Borman, Richard Millan, Zach Bennett
 * @date 4/12/2015
 */
#include <avr/io.h>

/// Initialize Bluetooth Transmission
void init_bluetooth(unsigned long baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)(baud);
	UCSR0A = 0b00000010;
	UCSR0C = 0b00001110;
	UCSR0B = 0b00011000;
}

/// Transmit a Single Character
void serial_putc(unsigned char data)
{
	while((UCSR0A & 0b00100000) == 0);
	UDR0 = data;
}

/// Transmit a Formatted String
void serial_puts(unsigned char x[])
{
    int i;
	for(i = 0; i < strlen(x); i++)
	{
		serial_putc(x[i]);
	}
}

/// Receive a Single Character
unsigned char serial_getc()
{
	while((UCSR0A & 0b10000000) == 0);
	return UDR0;
}