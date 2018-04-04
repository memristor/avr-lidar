#ifndef _XV11_H_
#define _XV11_H_

// Reference: https://xv11hacking.wikispaces.com/LIDAR+Sensor

// sqrt(3000^2 + 2000^2) + little bit more for core algorithms (394)
#include "Config.h"

typedef enum _packet_phase_t {
	PHASE_START = 0,
	PHASE_READ
} packet_phase_t;

extern void xv11_init(void);
extern void xv11_update(void);

#endif
