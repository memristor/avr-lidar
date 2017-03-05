#include "circbuff.h"

static inline volatile unsigned char* circ_inc(volatile unsigned char* address, volatile unsigned char* min, volatile unsigned char* max) {
	if (address < max - 1) {
		return address + 1;
	} else {
		return min;
	}
} 

unsigned char circbuff_size(volatile circbuff_t* circbuff) {
	if (circbuff->end >= circbuff->start) {
		return (circbuff->end - circbuff->start);
	} else {
		return CIRCBUFF_LENGTH - (circbuff->start - circbuff->end);
	}
}

void circbuff_init(volatile circbuff_t* circbuff) {
	circbuff->start = circbuff->data;
	circbuff->end = circbuff->data;
}

bool circbuff_is_full(volatile circbuff_t* circbuff) {
	return (circbuff_size(circbuff) >= CIRCBUFF_LENGTH - 1);
}

bool circbuff_add(volatile circbuff_t* circbuff, unsigned char data) {
	bool status = false;
	if (circbuff_is_full(circbuff) == true) {
		circbuff->start = circ_inc(circbuff->start, circbuff->data, circbuff->data + CIRCBUFF_LENGTH);
		status = true;
	}
	*circbuff->end = data;
	circbuff->end = circ_inc(circbuff->end, circbuff->data, circbuff->data + CIRCBUFF_LENGTH);
	return status;
}

bool circbuff_is_empty(volatile circbuff_t* circbuff) {
	return circbuff->start == circbuff->end;
}

unsigned char circbuff_remove(volatile circbuff_t* circbuff) {
	if (circbuff_is_empty(circbuff) == false) {
		unsigned char data = *(circbuff->start);
		circbuff->start = circ_inc(circbuff->start, circbuff->data, circbuff->data + CIRCBUFF_LENGTH);
		return data;
	}
	return 0;
}
