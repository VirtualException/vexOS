#ifndef _CONV_H
#define _CONV_H

#include <vexos/lib/bool.h>
#include <vexos/lib/types.h>

long int    atoi(const char* str);

char*       itoa(long int n, char* str);
char*       utoa(unsigned long int n, char* str);
char*       itoa_f(long int n, char* str, size_t slots, char fill, bool is_signed);

char*       itohex(unsigned long int n, char* strn, bool caps);
char*       itohex_f(unsigned long int n, char* strn, bool caps, size_t slots, char fill);

#endif
