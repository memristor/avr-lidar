#include "utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile uint_least64_t timer_millis = 0;

ISR (TIMER1_COMPA_vect) {
    timer_millis++;
}

void utils_init(void) {
	// CTC mode, Clock/8
    TCCR1B |= (1 << WGM12) | (1 << CS11);
 
    // Load the high byte, then the low byte
    // into the output compare
    OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
    OCR1AL = (uint8_t)CTC_MATCH_OVERFLOW;

    // Enable the compare match interrupt
    TIMSK1 |= (1 << OCIE1A);
}

uint64_t utils_mills(void) {
	uint64_t ret;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        ret = timer_millis;
    }
    return ret;
}
