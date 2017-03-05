#ifndef _XV11_H_
#define _XV11_H_

#define XV11_BAUDRATE 115200
#define XV11_ID 8000

// Reference: https://xv11hacking.wikispaces.com/LIDAR+Sensor

typedef enum _packet_phase_t {
	PHASE_START = 0,
	PHASE_READ
} packet_phase_t;

extern void xv11_init(void);
extern void xv11_update(void);

#endif
