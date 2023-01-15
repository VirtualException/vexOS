#include <vlibc/stdlib.h>
#include <vlibc/stdbool.h>
#include <vlibc/string.h>

char*
itoa(long long int n, char* str) {

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

char* itohex(unsigned long long int n, char* strn, bool caps) {

    unsigned long int rem;
    unsigned long int quo = n;

    unsigned int hexalpha = caps ? 'A' - 10 : 'a' - 10;

    size_t i = 0;

    while (quo != 0) {

        rem = quo % 16;
 
        if (rem < 10) strn[i++] = rem + 48;
        else strn[i++] = rem + hexalpha;

        quo = quo / 16;

    }

    if (i == 0) strn[i++] = '0';
    strn[i] = '\0';


    ssize_t j = 0, s = i - 1;
    char t;

    while(j <= s) {

        t = strn[j];
        strn[j] = strn[s];
        strn[s] = t;

        j++;
        s--;

    }

    return strn;
}