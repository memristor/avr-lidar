#include "can.h"
#include <stdint.h>
#include <stdarg.h>
#include <avr/interrupt.h>

/**
 * Init CAN using default configuration
 * @return Error code
 */
uint8_t can_wrapper_init(void);

/**
 * Simple way to send message via CAN bus.
 * @warning Don't use this function if you are gaining for speed
 * @example can_wrapper_send(0x12, 3, 0x12, 0x23, 0x34);
 * @param id Device ID
 * @param length Message length
 * @param ... Data
 * @return Error code
 */
uint8_t can_wrapper_send(uint32_t id, uint8_t length, ...);