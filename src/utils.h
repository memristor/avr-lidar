#ifndef _UTILS_H_
#define _UTILS_H_

#include <inttypes.h>

#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 8)

void utils_init(void);
uint64_t utils_mills(void);

#endif
