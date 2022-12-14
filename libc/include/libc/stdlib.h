#ifndef _STDLIB_H
#define _STDLIB_H

#include <libc/stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 32767

void    srand(unsigned int seed);
int     rand(void);

unsigned int getseed();

char*   itoa(int n, char* str);
int     atoi(const char* str);

#endif