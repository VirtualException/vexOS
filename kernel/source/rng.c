#include <vexos/rng.h>

static uint32_t rng_holdrand	= 0;
static uint32_t rng_seed		= 0;

void
rng_init(uint32_t seed) {

	rng_seed 		= seed;
	rng_holdrand	= seed;

}

uint32_t
rng_rand() {

	/*
	 * pseudo-Random Number Generator based on the MSVC Implementation of a
	 * Linear Congruential Generator, aka the 'rand()' function.
	 *
	 * Modulus = 2^32
	*/

	return (((rng_holdrand = rng_holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}
