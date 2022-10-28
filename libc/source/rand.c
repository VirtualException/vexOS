#include <libc/stdlib.h>

static int Seed;

void
srand(unsigned int seed) {
	Seed = seed;
}

int
rand(void) {

	long unsigned int hi, lo;

	lo = 16807 * (Seed & 0xFFFF);
	hi = 16807 * (Seed >> 16);

	lo += (hi & 0x5FFF) << 16;
	lo += hi >> 15;

	if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;

	return (Seed = lo);
}