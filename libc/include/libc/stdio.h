#ifndef _STDIO_H
#define _STDIO_H

#include <libc/stdint.h>
#include <libc/stddef.h>
#include <libc/vargs.h>

#define NULL ((void *)0)

int vprintf(const char* fmt, va_list vargs);
int printf(const char* fmt, ...);
int puts(const char* str);
int putchar(char c);

int vprintk(const char* fmt, va_list vargs);
int printk(const char* fmt, ...);
int putsk(const char* str);
int putchark(char c);

#endif