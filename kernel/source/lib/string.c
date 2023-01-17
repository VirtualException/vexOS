#include <vexos/lib/string.h>

size_t
strlen(const char* str) {

    size_t s = 0;

    while (*str++ != '\0') {
        s++;
    }

    return s;

}

void
strrev(char* str) {

    size_t i = 0;
    size_t s = strlen(str) - 1;

    for (char c; i < s; i++, s--) {
        c = str[i];
        str[i] = str[s];
        str[s] = c;
    }

}

char*
strcat(char *dest, const char *src) {

    char* ptr = dest + strlen(dest);

    while (*src != '\0') {
        *ptr++ = *src++;
    }

    *ptr = '\0';

    return dest;
}