#include <libc/mem.h>
#include <libc/stdlib.h>

bool
memcmp(const void* aptr, const void* bptr, size_t len) {

    const uint8_t* a = aptr;
    const uint8_t* b = bptr;

    for (uint64_t i = 0; i < len; i++) {
        if      (a[i] < b[i])   return -1;
        else if (a[i] > b[i])   return 1;
    }
    return EXIT_SUCCESS;
}

int
memcpy(const void* src, void* dest, size_t len) {

    uint8_t         *d  = dest;
    const uint8_t   *s  = src;

    while (len--) {
        *d++ = *s++;
    }

    return EXIT_SUCCESS;
}