#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include <can/can.h>
#include <can/can_wrapper.h>
#include "CanBus.h"
#include "xv11.h"
#include "regulation.h"
#include "Config.h"

int main(void) {

    // Init CAN bus
	CANbus_Init();

	can_t msg;
	msg.id = XV11_ID;
	msg.flags.rtr = 0;
	msg.flags.extended = 1;
	msg.data[0] = 0xab;
	msg.data[1] = 0xcd;
	msg.length = 2;
	can_send_message(&msg);
    // Init lidar (XV-11)
    xv11_init();

    // Init regulation for lidar
    regulation_init();

    // Enable interruputs
	sei();

    while(true) {
			xv11_update();
		}

	return 0;
}
