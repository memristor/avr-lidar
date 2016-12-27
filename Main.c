#include <util/delay.h>
#include <avr/io.h>
#include "config.h"
#include "can/can_lib.h"

#define MY_ID_TAG 0x80

int main(void) {
	DDRA = 0xFF;


	can_init(0);

	U8  sensor_buffer[8] = "Darko";
	st_cmd_t sensor_message;
	sensor_message.pt_data = sensor_buffer;
	sensor_message.ctrl.ide = 0;            //- CAN 2.0A
	sensor_message.dlc = 4;                 //- Message with 4-byte data
	sensor_message.id.std = MY_ID_TAG;
	sensor_message.cmd = CMD_REPLY_MASKED;

	while (1) {
		//PORTA = 0x0;
		//_delay_ms(200);
		//PORTA = 0xFF;
		//_delay_ms(200);

		while(can_cmd(&sensor_message) != CAN_CMD_ACCEPTED);
		//while(can_get_status(&sensor_message) == CAN_STATUS_NOT_COMPLETED);
	}


	return 0;
}
