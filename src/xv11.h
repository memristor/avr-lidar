#ifndef _XV11_H_
#define _XV11_H_

// Reference: https://xv11hacking.wikispaces.com/LIDAR+Sensor

// sqrt(3000^2 + 2000^2) + little bit more for core algorithms (394)
#define XV11_IGNORE_DISTANCE 4000 
#define XV11_BAUDRATE 115200
#define XV11_ID 0x00000100
#define XV11_IGNORE_CYCLES 0

typedef enum _packet_phase_t {
	PHASE_START = 0,
	PHASE_READ
} packet_phase_t;

extern void xv11_init(void);
extern void xv11_update(void);

#endif
