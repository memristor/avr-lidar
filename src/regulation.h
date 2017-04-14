#include <avr/io.h>
#include <util/delay.h>

#define REGULATION_SPEED 280
#define REGULATION_SPEED_TOLERANCE 20
#define REGULATION_MIN_DUTY 100
#define REGULATION_START_DUTY 150

void regulation_init(void);
void regulation_update(uint16_t);
