#include <libc/stdlib.h>
#include <libc/stdbool.h>
#include <libc/string.h>

char*
itoa(int n, char* str) {

    int i = 0;
    bool neg = 0;

    if (n < 0) {
         n = -n;
         neg = 1;
    }

    i = 0;

    do {
         str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (neg) {
         str[i++] = '-';
    }

    str[i] = '\0';

    strrev(str);

    return str;
}

int atoi(const char* str) {

    return str[0];
}