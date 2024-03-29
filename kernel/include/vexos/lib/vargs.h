#ifndef _VARGS_H
#define _VARGS_H

#include <vexos/lib/types.h>

/*          !!!!! WARNING !!!!!
*
*   This is a CUSTOM implementation for
*   variadic functions, supporting only
*   SysV ABI calling convention on x86_64
*   machines.
*
*/

typedef struct {

    unsigned long int args[9];
    unsigned long int index;

} va_list;

extern void                 __va_save(va_list* vargs);
extern unsigned long int    __va_next(va_list* vargs);

#define va_start(vargs)     __va_save(&(vargs))
#define va_arg(vargs)       __va_next(&(vargs))
#define va_end(vargs)       /* Do nothing */

#endif
