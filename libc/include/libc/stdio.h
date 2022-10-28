#ifndef _STDIO_H
#define _STDIO_H

#include <libc/types.h>
#include <libc/stddef.h>
#include <libc/vargs.h>

#define NULL ((void *)0)

#define ISBITSET(byte, n) ((status & (128 >> n)) == 1)


int vprintf(const char* fmt, va_list vargs);
int printf(const char* fmt, ...);
int printfat(unsigned int x, unsigned int y, const char* fmt, ...);
int putchar(char c);

#endif