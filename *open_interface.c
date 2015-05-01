/**
 * Open Interface Function - provided for us
 * @author See "Robotics Primer Workbook" project hosted on SourceForge.Net; Edited for clarity by Chad Nelson
 * @date 06/26/2012
 */

// Includes
#include <stdlib.h>
#include "util.h"
#include "open_interface.h"

// Allocate memory for a the sensor data
oi_t* oi_alloc()
{
	return calloc(1, sizeof(oi_t));
}

// Free memory from a pointer to the sensor data struct
void oi_free(oi_t *self)
{
	free(self);
}

// Initialize the Create
void oi_init(oi_t *self)
{
	UBRR1L = 16;
	UCSR1B = (1 << RXEN) | (1 << TXEN);
	UCSR1C = (3 << UCSZ10);
	oi_byte_tx(OI_OPCODE_START);
	oi_byte_tx(OI_OPCODE_BAUD);
	oi_byte_tx(8);
	wait_ms(100);
	UBRR1L = 33;
	oi_byte_tx(OI_OPCODE_FULL);
	oi_set_leds(1, 1, 7, 255);
	oi_update(self);
	oi_update(self);
}

// Update the Create. This will update all the sensor data and store it in the oi_t struct.
void oi_update(oi_t *self)
{
	int i;
	while (UCSR1A & (1 << RXC))
		i = UDR1;
	oi_byte_tx(OI_OPCODE_SENSORS);
	oi_byte_tx(OI_SENSOR_PACKET_GROUP6);
	char *sensor = (char *) self;
	for (i = 0; i < 52; i++) {
		*(sensor++) = oi_byte_rx();
	}
	sensor = (char *) self;
	self->distance                 = (sensor[12] << 8) + sensor[13];
	self->angle                    = (sensor[14] << 8) + sensor[15];
	self->voltage                  = (sensor[17] << 8) + sensor[18];
	self->current                  = (sensor[19] << 8) + sensor[20];
	self->charge                   = (sensor[22] << 8) + sensor[23];
	self->capacity                 = (sensor[24] << 8) + sensor[25];
	self->wall_signal              = (sensor[26] << 8) + sensor[27];
	self->cliff_left_signal        = (sensor[28] << 8) + sensor[29];
	self->cliff_frontleft_signal   = (sensor[30] << 8) + sensor[31]; 
	self->cliff_frontright_signal  = (sensor[32] << 8) + sensor[33];
	self->cliff_right_signal       = (sensor[34] << 8) + sensor[35];
	self->cargo_bay_voltage        = (sensor[41] << 8) + sensor[42];
	self->requested_velocity       = (sensor[48] << 8) + sensor[42];
	self->requested_radius         = (sensor[50] << 8) + sensor[51];
	self->requested_right_velocity = (sensor[52] << 8) + sensor[53];
	self->requested_left_velocity  = (sensor[54] << 8) + sensor[55];
	wait_ms(20);
}

// Sets the LEDs on the iRobot.
void oi_set_leds(uint8_t play_led, uint8_t advance_led, uint8_t power_color, uint8_t power_intensity)
{
	oi_byte_tx(OI_OPCODE_LEDS);
	oi_byte_tx(advance_led << 3 && play_led << 2);
	oi_byte_tx(power_color);
	oi_byte_tx(power_intensity);
}

// Drive wheels directly; speeds are in mm / sec
void oi_set_wheels(int16_t right_wheel, int16_t left_wheel)
{
	oi_byte_tx(OI_OPCODE_DRIVE_WHEELS);
	oi_byte_tx(right_wheel>>8);
	oi_byte_tx(right_wheel & 0xff);
	oi_byte_tx(left_wheel>>8);
	oi_byte_tx(left_wheel& 0xff);
}

// Loads a song onto the iRobot Create
void oi_load_song(int song_index, int num_notes, unsigned char *notes, unsigned char *duration)
{
	int i;
	oi_byte_tx(OI_OPCODE_SONG);
	oi_byte_tx(song_index);
	oi_byte_tx(num_notes);
	for (i=0;i<num_notes;i++) {
		oi_byte_tx(notes[i]);
		oi_byte_tx(duration[i]);
	}
}

// Plays a given song; use oi_load_song(...) first
void oi_play_song(int index)
{
	oi_byte_tx(OI_OPCODE_PLAY);
	oi_byte_tx(index);
}

// Runs default go charge program; robot will search for dock
void go_charge(void)
{
	char charging_state=0;
	oi_byte_tx(OI_OPCODE_MAX);
	oi_byte_tx(0x01);
	DDRB &= ~0x80;
	PORTB |= 0x80;
	do
    {
		charging_state = PINB >> 7;
	}
    while (charging_state == 0);
}

// Transmit a byte of data over the serial connection to the Create
void oi_byte_tx(unsigned char value)
{
	while (!(UCSR1A & (1 << UDRE)));
	UDR1 = value;
}

// Receive a byte of data from the Create serial connection. Blocks until a byte is received.
unsigned char oi_byte_rx(void)
{
	while (!(UCSR1A & (1 << RXC)));
	return UDR1;
}