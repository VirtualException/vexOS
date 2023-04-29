#include <vexos/vtt.h>
#include <vexos/printk.h>
#include <vexos/memory.h>
#include <vexos/lib/string.h>
#include <vexos/lib/conv.h>
#include <vexos/lib/def.h>
#include <vexos/info/kinfo.h>
#include <vexos/info/kinfo.h>
#include <vexos/arch/serial.h>


char LOGFMT[DEF_STR_LEN] = "[VexOS KRNL %d:%d:%d]: ";


int
vsprintk(char* str, const char* fmt, va_list vargs) {

    do { /* while (*fmt++ != '\0') */

    char buff[256] = { 0 };

    /* Format-only handeling */
    switch (*fmt) {

        case '%':

            switch (*++fmt) {

            case '%':
                buff[0] = *fmt;
                strcat(str, buff);
                break;

            case 'c':
            case 'C':
                buff[0] = va_arg(vargs);
                strcat(str, buff);
                break;

            case 'd':
            case 'D':
                itoa(va_arg(vargs), buff);
                strcat(str, buff);
                break;

            case 'x':
                itohex((unsigned long int) va_arg(vargs), buff, false);
                strcat(str, buff);
                break;

            case 'X':
                itohex((unsigned long int) va_arg(vargs), buff, true);
                strcat(str, buff);
                break;

            case 's':
            case 'S':
                strcat(str, (char*) va_arg(vargs));
                break;

            default:
                break;
            }

            break;

        default:
            buff[0] = *fmt;
            strcat(str, buff);
            break;
    }

    } while(*fmt++ != '\0');

    return EXIT_SUCCESS;
}

int
sprintk(char* str, const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    va_arg(vargs); // skip non variable argument

    vsprintk(str, fmt, vargs);

    va_end(vargs);

    return EXIT_SUCCESS;
}

int
vprintk(const char* fmt, va_list vargs) {

    do { /* while (*fmt++ != '\0') */

    char str[256] = { 0 };

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
                itoa(va_arg(vargs), str);
                putsk(str);
                break;

            case 'x':
                itohex(va_arg(vargs), str, false);
                putsk(str);
                break;

            case 'X':
                itohex(va_arg(vargs), str, true);
                putsk(str);
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

    return EXIT_SUCCESS;
}

int
printk(const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    bool kern_log = false;

    char out_buff[DEF_STR_LEN] = { 0 };
    char logheader[DEF_STR_LEN] = { 0 };

    uefi_time time;

    if (*fmt == KERN_LOG_ASCII) {

        kern_log = true;
        fmt++;

        kinfo->get_time(&time, 0);
        sprintk(logheader, LOGFMT, time.hour, time.minute, time.second);

        putsk(logheader);
        serial_print(logheader);

    }

    vsprintk(out_buff, fmt, vargs);

    vprintk(out_buff, vargs);
    if (kern_log) serial_print(out_buff);

    va_end(vargs);

    return EXIT_SUCCESS;
}

int
putsk(const char* str) {

    for (size_t i = 0; str[i] != '\0'; i++) {
        putchark(str[i]);
    }

    return EXIT_SUCCESS;
}


int
putchark(char c) {

    vtt_putchar(&vtts[VTTS_KLOG], c);

    return c;

}
