#ifndef _MEMORY_H
#define _MEMORY_H

#include <vexos/lib/types.h>
#include <vexos/lib/bool.h>

bool        memcmp(const void* aptr, const void* bptr, size_t len);
int         memcpy(const void* src, void* dest, size_t len);
extern void memset(void* dest, uint32_t size, uint8_t val);
extern void memset32(void* dest, uint32_t size, uint32_t val);

#endif