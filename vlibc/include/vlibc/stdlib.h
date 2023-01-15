#ifndef _STDLIB_H
#define _STDLIB_H

#include <vlibc/stddef.h>
#include <vlibc/stdbool.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 32767

void    srand(unsigned int seed);
int     rand(void);

char*   itoa(long long int n, char* str);
int     atoi(const char* str);

char*   itohex(unsigned long long int n, char* strn, bool caps);

#endif