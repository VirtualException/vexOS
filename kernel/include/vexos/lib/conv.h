#ifndef _CONV_H
#define _CONV_H

#include <vexos/lib/bool.h>

char*   itoa(long long int n, char* str);
int     atoi(const char* str);

char*   itohex(unsigned long long int n, char* strn, bool caps);

#endif