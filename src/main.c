#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include <can/can.h>
#include <can/can_wrapper.h>
#include "xv11.h"

int main(void) {
    can_wrapper_init();
    xv11_init();
	sei();
    
    can_wrapper_send(XV11_ID, 1, 1);
    
    while(true) {
		xv11_update();
		//_delay_ms(100);
	}
	
	return 0;
}
