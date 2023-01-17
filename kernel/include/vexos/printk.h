#ifndef _PRINTK_H
#define _PRINTK_H

#include <vexos/lib/vargs.h>

#define KERN_LOG_ASCII  '\1'
#define KERN_LOG        "\1"


int vsprintk(char *str, const char *fmt, va_list vargs);
int sprintk(char *str, const char *fmt, ...);

int vprintk(const char* fmt, va_list vargs);
int printk(const char* fmt, ...);

int putsk(const char* str);
int putchark(char c);

#endif