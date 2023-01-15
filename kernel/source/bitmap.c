#include <vexos/bitmap.h>

void bitmap_set(bitmap_t b, int i, bool val) {

    if (val)    b[i / 8] |= 1 << (i & 7);
    else        b[i / 8] |= ~(1 << (i & 7));

}

int bitmap_get(bitmap_t b, int i) {

    return      b[i / 8] & (1 << (i & 7)) ? 1 : 0;

}