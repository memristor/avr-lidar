#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include "can.h"
#include "can_wrapper.h"

uint8_t lastState = 0;
uint8_t state = 0;

int main(void) {
    can_wrapper_init();

    DDRA = 0x00;

    while (1) {
        state = (PINA & (1 << PD3)) >> PD3;
        if (state != lastState) {
            lastState = state;
            can_wrapper_send(0x08, 1, state);
        }

        // Check if a new messag was received
        if (can_check_message()) {
            can_t msg;

            // Try to read the message
            if (can_get_message(&msg)) {
                msg.data[0]++;
                can_send_message(&msg);
            }
        }
    }
	
	return 0;
}