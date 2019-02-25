#include "regulation.h"
#include <can/can_wrapper.h>

static void update_speed(void);
static uint8_t duty = REGULATION_START_DUTY;

void regulation_init(void) {
    // TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<CS00);
    TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0B1)|(1<<CS00);

	//Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
    // DDRB |= (1 << PB7);
    // PORTB &= ~(1 << PB7);
    
    DDRC |= (1 << PC1);
    PORTC &= ~(1 << PC1);
   
    // Set initial speed
    update_speed();
}

void update_speed(void) {
    OCR0A = duty;
}

void regulation_update(uint16_t tmp_speed) {
    if(tmp_speed < REGULATION_SPEED - REGULATION_SPEED_TOLERANCE) {
        duty = (duty + 1 > 255) ? 255 : duty + 1;
    } else if (tmp_speed > REGULATION_SPEED + REGULATION_SPEED_TOLERANCE) {
        duty = (duty - 1 < REGULATION_MIN_DUTY) ? REGULATION_MIN_DUTY : duty - 1;
    }
    update_speed();
}
