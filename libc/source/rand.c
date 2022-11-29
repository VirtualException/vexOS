#include <libc/stdlib.h>

static int _seed = 0;

void
srand(unsigned int seed) {
	_seed = seed;
}

int
rand(void) {

	long unsigned int hi = 0;
	long unsigned int lo = 0;

	lo = 16807 * (_seed & 0xFFFF);
	hi = 16807 * (_seed >> 16);

	lo += (hi & 0x5FFF) << 16;
	lo += hi >> 15;

	if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;

	return (_seed = lo);
}
