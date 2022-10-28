#include <libc/stdlib.h>
#include <libc/string.h>

char* itoa(int n, char* str) {

    int i = 0;
    int sign = n;

    if (sign < 0) n = -n;

    while ((n /= 10) > 0) {
        str[i++] = n % 10 + '0';
    }

    if (sign < 0) str[i++] = '-';

    str[i] = '\0';

    strrev(str);

    return str;
}

int atoi(const char* str) {

    return str[0];
}