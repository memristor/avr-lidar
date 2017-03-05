#include <avr/io.h>
#include <util/delay.h>

#define _SPEED 100

void regulation_init(void);
void set_speed(uint8_t);
void regulation_update(uint16_t);
