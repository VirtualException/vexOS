#ifndef _PRINTK_H
#define _PRINTK_H

#include <vexos/lib/vargs.h>

#define KERN_LOG        "\1"    /* Just treat message as log info */
#define KERN_TLOG       "\2"    /* Add time headding to the log info */

#define KERN_LOG_ASCII  '\1'
#define KERN_TLOG_ASCII '\2'

/* As ANSI Escape Codes are fucked up, i make my own implementation */

/* ... */

int kvsprintf(char *str, const char *fmt, va_list vargs);
int ksprintf(char *str, const char *fmt, ...);

int kvprintf(const char* fmt, va_list vargs);
int kprintf(const char* fmt, ...);

int kputs(const char* str);
int kputchar(char c);

#endif
