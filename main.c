#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include "can.h"
#include "can_wrapper.h"
#include "pwm.h"
#include "serial.h"

uint8_t lastState = 0;
uint8_t state = 0;

void InitPWM(void)
{

   TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<CS00);

   DDRB |= (1 << PB7);
   PORTB &= ~(1 << PB7);
}


void SetPWMOutput(uint8_t duty)
{
   OCR0A=duty;
}


int main(void) {
    can_wrapper_init();
    InitPWM();
    
 //   initUart(9600);

    DDRA = 0x00;
    PORTA = 0x00;
    
   // SetPWMOutput(168);

    while (1) {
        
        state = (PIND & (1 << PD3)) >> PD3;
        if (state != lastState) {
            lastState = state;
            can_wrapper_send(0x08, 1, state);
        }
        if ((PINA & (1 << PA0)) == 0){
            SetPWMOutput(168);
            _delay_ms(2000);
            SetPWMOutput(0);
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
