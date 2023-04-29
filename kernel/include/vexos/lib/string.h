#ifndef _STRING_H
#define _STRING_H

#include <vexos/lib/types.h>

#define DEF_STR_LEN 1024

size_t  strlen(const char* str);
void    strrev(char* str);
char*   strcat(char *dest, const char *src);

#endif