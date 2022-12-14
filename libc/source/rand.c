#include <libc/stdlib.h>

static unsigned long int holdrand = 1;

void
srand(unsigned int seed) {
	holdrand = seed;
}

int
rand() {
	return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}

unsigned int
getseed() {
	return holdrand;
}
