/**
 * Open Interface Function - provided for us
 * @author See "Robotics Primer Workbook" project hosted on SourceForge.Net; Edited for clarity by Chad Nelson
 * @date 06/26/2012
 */

#ifndef CREATE_H
#define CREATE_H

// Includes
#include <inttypes.h>
#include <avr/io.h>

// Defines
#define FOSC 16000000
#define OI_OPCODE_START            128
#define OI_OPCODE_BAUD             129
#define OI_OPCODE_CONTROL          130
#define OI_OPCODE_SAFE             131
#define OI_OPCODE_FULL             132
#define OI_OPCODE_POWER            133
#define OI_OPCODE_SPOT             134
#define OI_OPCODE_CLEAN            135
#define OI_OPCODE_MAX              136
#define OI_OPCODE_DRIVE            137
#define OI_OPCODE_MOTORS           138
#define OI_OPCODE_LEDS             139
#define OI_OPCODE_SONG             140
#define OI_OPCODE_PLAY             141
#define OI_OPCODE_SENSORS          142
#define OI_OPCODE_FORCEDOCK        143
#define OI_OPCODE_PWM_MOTORS       144
#define OI_OPCODE_DRIVE_WHEELS     145
#define OI_OPCODE_DRIVE_PWM        146
#define OI_OPCODE_OUTPUTS          147
#define OI_OPCODE_STREAM           148
#define OI_OPCODE_QUERY_LIST       149
#define OI_OPCODE_DO_STREAM        150
#define OI_OPCODE_SEND_IR_CHAR     151
#define OI_OPCODE_SCRIPT           152
#define OI_OPCODE_PLAY_SCRIPT      153
#define OI_OPCODE_SHOW_SCRIPT      154
#define OI_OPCODE_WAIT_TIME        155
#define OI_OPCODE_WAIT_DISTANCE    156
#define OI_OPCODE_WAIT_ANGLE       157
#define OI_OPCODE_WAIT_EVENT       158
#define OI_SENSOR_PACKET_GROUP0 0
#define OI_SENSOR_PACKET_GROUP1 1
#define OI_SENSOR_PACKET_GROUP2 2
#define OI_SENSOR_PACKET_GROUP3 3
#define OI_SENSOR_PACKET_GROUP4 4
#define OI_SENSOR_PACKET_GROUP5 5
#define OI_SENSOR_PACKET_GROUP6 6
#define MIN(a,b) ((a < b) ? (a) : (b))
#define MAX(a,b) ((a > b) ? (a) : (b))
#define PIN_0 0x01
#define PIN_1 0x02
#define PIN_2 0x04
#define PIN_3 0x08
#define PIN_4 0x10
#define PIN_5 0x20
#define PIN_6 0x40
#define PIN_7 0x80

// iRobot Create Sensor Data
typedef struct
{
	uint8_t bumper_right : 1;
	uint8_t bumper_left : 1;
	uint8_t wheeldrop_right : 1;
	uint8_t wheeldrop_left : 1;
	uint8_t wheeldrop_caster : 1;
	uint8_t wall;
	uint8_t cliff_left;
	uint8_t cliff_frontleft;
	uint8_t cliff_frontright;
	uint8_t cliff_right;
	uint8_t virtual_wall;
	uint8_t overcurrent_ld1 : 1;
	uint8_t overcurrent_ld0 : 1;
	uint8_t overcurrent_ld2 : 1;
	uint8_t overcurrent_driveright : 1;
	uint8_t overcurrent_driveleft : 1;
	uint16_t unused_bytes;
	uint8_t infrared_byte;
	uint8_t button_play : 2;
	uint8_t button_advance : 1;
	int16_t distance;
	int16_t angle;
	uint8_t charging_state;
	uint16_t voltage;
	int16_t current;
	int8_t temperature;
	uint16_t charge;
	uint16_t capacity;
	uint16_t wall_signal;
	uint16_t cliff_left_signal;
	uint16_t cliff_frontleft_signal;
	uint16_t cliff_frontright_signal;
	uint16_t cliff_right_signal;
	uint8_t cargo_bay_io0 : 1;
	uint8_t cargo_bay_io1 : 1;
	uint8_t cargo_bay_io2 : 1;
	uint8_t cargo_bay_io3 : 1;
	uint8_t cargo_bay_baud : 1;
	uint16_t cargo_bay_voltage;
	uint8_t internal_charger_on : 1;
	uint8_t home_base_charger_on : 1;
	uint8_t oi_mode;
	uint8_t song_number;
	uint8_t song_playing;
	uint8_t number_packets;
	int16_t requested_velocity;
	int16_t requested_radius;
	int16_t requested_right_velocity;
	int16_t requested_left_velocity;
} oi_t;

typedef oi_t oi_sensors_t;

// Allocate memory for the oi_sensor_t struct
oi_t * oi_alloc();

// Initialize the Create. This must be called first.
void oi_init(oi_t *self);
void oi_free(oi_t *self);

// Update the Create. This will update all the sensor data.
void oi_update(oi_t *self);

// Set the LEDS on the Create
void oi_set_leds(uint8_t play_led, uint8_t advance_led, uint8_t power_color, uint8_t power_intensity);

// Set direction and speed of the robot's wheels
void oi_set_wheels(int16_t right_wheel, int16_t left_wheel);

// Transmit a byte of data over the serial connection to the Create
void oi_byte_tx(unsigned char value);

// Receive a byte of data from the Create serial connection.
unsigned char oi_byte_rx(void);

// Load song sequence
void oi_load_song(int song_index, int num_notes, unsigned char  *notes, unsigned char  *duration);

// Play song
void oi_play_song(int index);

// Calls in built in demo to send the iRobot to an open home base. This will cause the iRobot to enter the Passive state.
void go_charge(void);

#endif // CREATE_H