#include <vexos/lib/rng.h>

static unsigned long int holdrand = 1;

void
rng_init(unsigned long int seed) {
	holdrand = seed;
}

int
rng_rand(void) {
	return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}
