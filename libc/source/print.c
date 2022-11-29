#include <libc/stdio.h>
#include <libc/stdlib.h>

int
puts(const char* str) {

    if (str == NULL) return -1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }

    return 0;
}

int
putsk(const char* str) {

    if (str == NULL) return -1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        putchark(str[i]);
    }

    return 0;
}

int
vprintf(const char* fmt, va_list vargs) {

    char buff[1024] = { 0 };

    do { /* while (*fmt++ != '\0') */

    /* Format-only handeling */
    switch (*fmt) {

        case '%':

            switch (*++fmt) {

            case '%':
                putchar('%');
                break;

            case 'c':
            case 'C':
                putchar(va_arg(vargs));
                break;

            case 'd':
            case 'D':
                int d = va_arg(vargs);
                itoa(d, buff);
                puts(buff);
                break;

            case 's':
            case 'S':
                puts((char*) va_arg(vargs));
                break;

            default:
                break;
            }

            break;

        default:
            putchar(*fmt);
            break;
    }

    } while(*fmt++ != '\0');

    return 0;
}

int
vprintk(const char* fmt, va_list vargs) {

    char buff[1024] = { 0 };

    do { /* while (*fmt++ != '\0') */

    /* Format-only handeling */
    switch (*fmt) {

        case '%':

            switch (*++fmt) {

            case '%':
                putchark('%');
                break;

            case 'c':
            case 'C':
                putchark(va_arg(vargs));
                break;

            case 'd':
            case 'D':
                int d = va_arg(vargs);
                itoa(d, buff);
                putsk(buff);
                break;

            case 's':
            case 'S':
                putsk((char*) va_arg(vargs));
                break;

            default:
                break;
            }

            break;

        default:
            putchark(*fmt);
            break;
    }

    } while(*fmt++ != '\0');

    return 0;
}

int
printf(const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    vprintf(fmt, vargs);

    va_end(vargs);

    return EXIT_SUCCESS;
}

int
printk(const char *fmt, ...) {

    va_list vargs;
    va_start(vargs);

    //putsk("[VEXOS_KERN]: ");

    vprintk(fmt, vargs);

    va_end(vargs);

    return EXIT_SUCCESS;
}
