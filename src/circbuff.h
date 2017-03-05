#ifndef _CIRCBUFF_H_
#define _CIRCBUFF_H_

#include <stdint.h>
#include <stdbool.h>

#define CIRCBUFF_LENGTH 100U

typedef struct _circbuff_t {
	volatile unsigned char data[CIRCBUFF_LENGTH];
	volatile unsigned char* start;
	volatile unsigned char* end;
	
} circbuff_t;

void circbuff_init(volatile circbuff_t* circbuff);
bool circbuff_is_full(volatile circbuff_t* circbuff);
bool circbuff_add(volatile circbuff_t* circbuff, unsigned char data);
unsigned char circbuff_remove(volatile circbuff_t* circbuff);
bool circbuff_is_empty(volatile circbuff_t* circbuff);
unsigned char circbuff_size(volatile circbuff_t* circbuff);

#endif
