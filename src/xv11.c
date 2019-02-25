#include "xv11.h"

#include <stdbool.h>
#include <avr/io.h>
#include <can/can_wrapper.h>
#include <can/can.h>


#include "regulation.h"
#include "circbuff.h"
#include "uart.h"

static uint16_t calculate_checksum(uint8_t* data);
static uint8_t try_parse_and_send(void);

static volatile circbuff_t recv_buffer;
static packet_phase_t phase = PHASE_START;
static uint8_t ignored_cycles = 0;
static bool msg_send_enabled = true;

void xv11_init(void) {
	circbuff_init(&recv_buffer);
	uart_init(XV11_BAUDRATE,0);
}

uint16_t calculate_checksum(uint8_t* data) {
	size_t t;
	uint16_t data_list[10];
	uint32_t chk32;
	uint16_t checksum;

	// Group the data by word, little-endian
	for (t = 0; t < 10; t++) {
		data_list[t] = data[2 * t] + (data[2 * t + 1] << 8);
	}

	// Compute the checksum on 32 bits
	chk32 = 0;
	for (t = 0; t < 10; t++) {
		chk32 = (chk32 << 1) + data_list[t];
	}

	// Return a value wrapped around on 15bits, and truncated to still fit into 15 bits
	checksum = (chk32 & 0x7FFF) + (chk32 >> 15);
	checksum = checksum & 0x7FFF;
	return checksum;
}

uint8_t try_parse_and_send(void) {
	size_t i;
	uint8_t packet[22];
	uint8_t index;
	uint16_t speed;
	bool invalid_data;
	bool strength_warning;
	uint16_t distance;
	uint16_t angle;
	uint16_t checksum;
	uint16_t quality;


	// Set phase
	phase = PHASE_START;


	// Make an array
	packet[0] = 0xFA;
	for (i = 1; i < 22; i++) {
		packet[i] = circbuff_remove(&recv_buffer);
	}


	// Check checksum
	checksum = (packet[21] << 8) | packet[20];
	if (checksum != calculate_checksum(packet)) {
		return 1;
	}

	// Parse packet
	index = packet[1];
	speed = (packet[3] << 8) | packet[2];
	speed >>= 6; // Ignore decimals

	for (i = 0; i < 4; i++) {
		uint8_t byte0 = packet[4 * (1 + i)];
		uint8_t byte1 = packet[4 * (1 + i) + 1];
		uint8_t byte2 = packet[4 * (1 + i) + 2];
		uint8_t byte3 = packet[4 * (1 + i) + 3];

		invalid_data = (byte1 & 0x80) >> 7;
		strength_warning = (byte1 & 0x40) >> 6;
		distance = ((byte1 & 0x3f) << 8) | byte0;
		angle = (index - 0xA0) * 4 + i;
		quality = (byte3 << 8) | byte2;

		if (angle == 0) {
			ignored_cycles++;
			if (ignored_cycles >= XV11_IGNORE_CYCLES) {
				ignored_cycles = 0;
				msg_send_enabled = true;
			} else {
				msg_send_enabled = false;
			}
		}


		// Ignore some data
		if (invalid_data == 1 || strength_warning == 1 || distance > XV11_IGNORE_DISTANCE) {
			continue;
		}

		// Send CAN message
		if (msg_send_enabled == true) {
			can_t msg;
			msg.id = XV11_ID;
			msg.flags.rtr = 0;
			msg.flags.extended = 1;
			msg.data[0] = ((angle & 0x7F00) >> 8);
			msg.data[1] = angle & 0xff;
			msg.data[2] = (distance & 0xff00) >> 8;
			msg.data[3] = distance & 0xff;
			msg.length = 4;
			can_send_message(&msg);
		}
    }

	regulation_update(speed);

	return 0;
}

void xv11_update(void) {
	while(uart_available()) {
		circbuff_add(&recv_buffer, uart_read());
	}
	
	if (phase == PHASE_START) {
		unsigned char data = circbuff_remove(&recv_buffer);
		if (data == 0xFA) {
			phase = PHASE_READ;
		}
	} else {
		if (circbuff_size(&recv_buffer) >= 22 - 1) {
			try_parse_and_send();
		}
	}
}
