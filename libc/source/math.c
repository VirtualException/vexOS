#include <libc/types.h>
#include <libc/math.h>

float cos(float x) {

    double xx;
    int8_t sign = 1;

    if (x > M_PI) {
        x -= M_PI;
        sign = -1;
    }

    xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)));

}

float sin(float x) {
    return cos(x - M_PI / 2);
}