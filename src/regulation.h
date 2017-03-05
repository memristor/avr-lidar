#include <avr/io.h>
#include <util/delay.h>

#define REGULATION_SPEED 300
#define REGULATION_MIN_DUTY 100

void regulation_init(void);
void regulation_update(uint16_t);
