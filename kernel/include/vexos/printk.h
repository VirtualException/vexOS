#ifndef _PRINTK_H
#define _PRINTK_H

#include <vexos/lib/vargs.h>
#include <vexos/lib/attributes.h>

/* #define MODULE(name)    static const char __MODULE__[] = name; */

#define KERN_LOG        "\1"    /* Just treat message as log info */
#define KERN_TLOG       "\2"    /* Add time heading to the log info */

#define KERN_LOG_ASCII  '\1'
#define KERN_TLOG_ASCII '\2'

/* As ANSI Escape Codes are fucked up, i should make my own implementation */

//#define printk(fmt, ...)    __printk(KERN_TLOG "%s" fmt, __FILE__ __VA_OPT__(,) __VA_ARGS__);
//#define dbgprintk(...)  __dbgprintk(__FILE__, __VA_ARGS__);

int __vsprintk(char *str, const char *fmt, va_list vargs);
int sprintk(char *str, const char *fmt, ...);

int __vprintk(const char* fmt, va_list vargs);
/* int __mprintk(const char* module, const char* fmt, ...); */
int printk(const char* fmt, ...);

int putsk(const char* str);
int putchark(char c);

#endif
