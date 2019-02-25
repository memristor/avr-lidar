#include <stdbool.h>
#include <avr/io.h>
void uart_init(unsigned long baud, char config);
int uart_available(void);
int uart_read(void);
