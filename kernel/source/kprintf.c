#include <vexos/vtt.h>
#include <vexos/kprintf.h>
#include <vexos/time.h>
#include <vexos/info/kinfo.h>

#include <vexos/lib/memory.h>
#include <vexos/lib/string.h>
#include <vexos/lib/conv.h>
#include <vexos/lib/def.h>

#include <vexos/iobus/serial.h>

#define KLOGFMT "[vexOSkernel %02d:%02d:%02d +%09d.%03dms]: "

int
kvsprintf(char* str, const char* fmt, va_list vargs) {

    size_t width = 0;
    char fill = ' ';

    do { /* while (*fmt++ != '\0') */

    char buff[256] = { 0 };

    /* Format-only handeling */
    switch (*fmt) {

        case '%':

            width = 0;
            fill = ' ';

format:

            switch (*++fmt) {

            case '%':

                buff[0] = *fmt;
                strcat(str, buff);
                break;

            case '0':

                fill = '0';
                goto format;
                break;

            case '1'...'9':

                buff[0] = *fmt;
                char next = *(fmt + 1);

                if (next >= '0' && next <= '9') {
                    buff[1] = next;
                    fmt++;
                }

                width = atoi(buff);
                goto format;
                break;

            case 'c':
            case 'C':

                buff[0] = va_arg(vargs);
                strcat(str, buff);
                break;

            case 'd':
            case 'D':

                itoa_f(va_arg(vargs), buff, width, fill);
                strcat(str, buff);
                break;

            case 'x':

                itohex_f((unsigned long int) va_arg(vargs), buff, false, width, fill);
                strcat(str, buff);
                break;

            case 'X':

                itohex_f((unsigned long int) va_arg(vargs), buff, true, width, fill);
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

    return strlen(str);
}

int
ksprintf(char* str, const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    va_arg(vargs); // skip non variable argument

    size_t count = 0;

    count += kvsprintf(str, fmt, vargs);

    va_end(vargs);

    return count;
}

int
kvprintf(const char* fmt, va_list vargs) {

    char str[DEF_STR_LEN] = { 0 };

    size_t count = 0;

    kvsprintf(str, fmt, vargs);

    count += kputs(str);

    return count;
}

int
kprintf(const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    time_t time;

    char out_buff[DEF_STR_LEN] = { 0 };
    char logheader[64] = { 0 };

    size_t count = 0;

    switch (*fmt) {

    case KERN_TLOG_ASCII:

        time_get(&time);

        uint64_t ms = time_ms_boot();

        ksprintf(logheader, KLOGFMT, time.hour, time.minute, time.second, (ms - ms % 1000) / 1000, ms % 1000);

        serial_print(logheader);
        count += kputs(logheader);

        __fallthrough;

    case KERN_LOG_ASCII:

        kvsprintf(out_buff, ++fmt, vargs); /* ! */

        serial_print(out_buff);
        count += kputs(out_buff);

        break;

    default:

        kvsprintf(out_buff, fmt, vargs); /* ! */
        count += kputs(out_buff);

        break;
    }

    va_end(vargs);

    return count;
}

int
kputs(const char* str) {

    size_t i;

    for (i = 0; str[i] != '\0'; i++) {
        kputchar(str[i]);
    }

    return i;
}


int
kputchar(char c) {

    vtt_putchar(&vtts[VTTS_KLOG], c);

    return c;

}
