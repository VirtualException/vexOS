#ifndef _STRING_H
#define _STRING_H

#include <vlibc/stddef.h>
#include <vlibc/stdbool.h>

size_t  strlen(const char* str);
void    strrev(char* str);
char*   strcat(char *dest, const char *src);

bool        memcmp(const void* aptr, const void* bptr, size_t len);
int         memcpy(const void* src, void* dest, size_t len);
extern void memset(void* dest, uint32_t size, uint8_t val);
extern void memset32(void* dest, uint32_t size, uint32_t val);

#endif