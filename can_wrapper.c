#include "can_wrapper.h"

uint8_t can_wrapper_init(void) {
    uint8_t status;

    // Initialize MCP2515
    status = can_init(BITRATE_125_KBPS);

    // Set filter to receive all messages
    can_filter_t filter = {
        .id = 0,
        .mask = 0,
        .flags = {
            .rtr = 0,
            .extended = 0
        }
    };
    can_set_filter(0, &filter);

    // Enable interrupts
    sei();

    return status;
}

uint8_t can_wrapper_send(uint32_t id, uint8_t length, ...) {
    can_t msg;
    va_list pl;
    uint_fast8_t i;

    msg.id = id;
    msg.flags.rtr = 0;
    msg.flags.extended = 1;
    msg.length = length;

    va_start(pl, length);
    for (i = 0; i < length; i++) {
        uint8_t x = va_arg(pl, int);
        msg.data[i] = x;
    }
    va_end(pl);

    return can_send_message(&msg);
}