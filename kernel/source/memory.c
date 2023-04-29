#include <vexos/memory.h>
#include <vexos/lib/def.h>

void*
memcpy(void* dest, const void* src, size_t n) {

    uint8_t         *d  = (uint8_t*) dest;
    const uint8_t   *s  = (uint8_t*) src;

    while (n--) *d++ = *s++;

    return dest;
}

void*
memset(void* s, int c, size_t n) {

    uint8_t*    ptr = (uint8_t*) s;
    uint8_t     val = (uint8_t) c;

    while (n--) *ptr++ = val;

    return s;
}

extern void*
memset32(void* s, int c, size_t n) {

    uint32_t*   ptr = (uint32_t*) s;
    uint32_t    val = (uint32_t) c;

    while (n--) *ptr++ = val;

    return s;
}

int
memcmp(const void* s1, const void* s2, size_t n) {

    const uint8_t* a = (uint8_t*) s1;
    const uint8_t* b = (uint8_t*) s2;

    for (uint64_t i = 0; i < n; i++) {
        if      (a[i] < b[i])   return -1;
        else if (a[i] > b[i])   return 1;
    }

    return 0;
}