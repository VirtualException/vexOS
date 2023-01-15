#ifndef _STDIO_H
#define _STDIO_H

#include <vlibc/stdint.h>
#include <vlibc/stddef.h>
#include <vlibc/vargs.h>


int vsprintf(char *str, const char *fmt, va_list vargs);
int sprintf(char *str, const char *fmt, ...);

int vprintf(const char* fmt, va_list vargs);
int printf(const char* fmt, ...);
int puts(const char* str);
int putchar(char c);

#endif