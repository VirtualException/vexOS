#ifndef _BITMAP_H
#define _BITMAP_H

#include <vexos/lib/bool.h>

typedef unsigned char* bitmap_t;

void    bitmap_set(bitmap_t b, int i, bool val);
int     bitmap_get(bitmap_t b, int i);

#endif