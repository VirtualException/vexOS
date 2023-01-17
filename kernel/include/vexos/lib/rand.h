#ifndef _RAND_H
#define _RAND_H

#include <vexos/lib/bool.h>

#define RAND_MAX 32767

void    srand(unsigned int seed);
int     rand(void);

#endif