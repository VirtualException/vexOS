#include <libc/string.h>

size_t
strlen(const char* str) {

    unsigned int s = 0;

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