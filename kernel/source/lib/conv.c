#include <vexos/lib/conv.h>
#include <vexos/lib/string.h>
#include <vexos/lib/memory.h>

long int
atoi(const char* str) {

    long int res = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        res = res * 10 + str[i] - '0';
    }

    return res;
}

char*
itoa(long int n, char* str) {
    return itoa_f(n, str, 0, '0');
}

char*
itoa_f(long int n, char* str, size_t width, char fill) {

    size_t i = 0;
    bool neg = false;

    if (n < 0) {
        n = -n;
        neg = 1;
    }

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (neg) {
        str[i++] = '-';
    }

    while (i < width) {
        str[i++] = fill;
    }

    str[i] = '\0';

    strrev(str);

    return str;
}

char*
itohex(unsigned long int n, char* str, bool caps) {
    return itohex_f(n, str, caps, 0, '0');
}

char*
itohex_f(unsigned long int n, char* str, bool caps, size_t width, char fill) {

    unsigned long int rem;
    unsigned long int quo = n;

    unsigned int hexalpha = caps ? 'A' - 10 : 'a' - 10;

    size_t i = 0;

    while (quo != 0) {

        rem = quo % 16;
 
        if (rem < 10) str[i++] = rem + 48;
        else str[i++] = rem + hexalpha;

        quo = quo / 16;

    }

    if (i == 0) str[i++] = '0';

    while (i < width) {
        str[i++] = fill;
    }

    str[i] = '\0';

    ssize_t j = 0, s = i - 1;
    char t;

    while(j <= s) {

        t = str[j];
        str[j] = str[s];
        str[s] = t;

        j++;
        s--;

    }

    return str;
}