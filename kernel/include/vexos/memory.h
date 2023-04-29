#ifndef _MEMORY_H
#define _MEMORY_H

#include <vexos/lib/types.h>
#include <vexos/lib/bool.h>

/* Standard safe!                       almost */

void*           memcpy(void *dest, const void *restrict src, size_t n);
void*           memset(void *s, int c, size_t n);
extern void*    memset32(void *s, int c, size_t n);
int             memcmp (const void *s1, const void *s2, size_t n);

#endif