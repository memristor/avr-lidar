#include "../src/circbuff.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
	size_t i;
	circbuff_t buff;
	
	circbuff_init(&buff);
	assert(circbuff_size(&buff) == 0);
	assert(circbuff_is_empty(&buff) == true);
	assert(circbuff_is_full(&buff) == false);

	
	circbuff_add(&buff, 53);
	assert(circbuff_size(&buff) == 1);
	assert(circbuff_is_empty(&buff) == false);
	assert(circbuff_is_full(&buff) == false);
	assert(circbuff_remove(&buff) == 53);
	assert(circbuff_is_empty(&buff) == true);
	assert(circbuff_is_full(&buff) == false);
	
	for (i = 0; i < 150; i++) {
		circbuff_add(&buff, 11);
	}
	assert(circbuff_size(&buff) == CIRCBUFF_LENGTH - 1);
	assert(circbuff_is_empty(&buff) == false);
	assert(circbuff_add(&buff, 11) == true);
	
	assert(circbuff_remove(&buff) == 11);
	assert(circbuff_size(&buff) == CIRCBUFF_LENGTH - 2);
	
	return 0;
}
