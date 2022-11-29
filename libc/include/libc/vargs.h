#ifndef _VARGS_H
#define _VARGS_H

/*          !!!!! WARNING !!!!!
*
*   This is a CUSTOM implementation for
*   variadic functions, supporting only
*   SysV ABI calling convention on x86_64
*   machines.
*
*/

typedef struct {

    unsigned long int args[5];
    unsigned int index;

} va_list;

extern void va_save(va_list* vargs);

#define va_start(vargs)     va_save(&(vargs))
#define va_arg(vargs)       ((vargs).args[(vargs).index++])
#define va_end(vargs)       /* Do nothing */

#endif