#ifndef _RNG_H
#define _RNG_H

#include <vexos/time.h>

void        rng_init(uint32_t seed);
uint32_t    rng_rand();

#endif
