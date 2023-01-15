#ifndef _KEYMAP_H
#define _KEYMAP_H

#include <vlibc/stdbool.h>

/* qemu (machine-specific)*/
#ifdef QEMU
    #define KBD_TIMEOUT         3000
    #define KBD_FIRST_TIMEOUT   24000
#else
    #define KBD_TIMEOUT         1500
    #define KBD_FIRST_TIMEOUT   12000
#endif

void    kbd_setup(void);
void    kbd_reset_timeout(void);
char    kbd_ps2ascii(int scancode, bool shift);
int     kbd_get_input(char* c, uint8_t* kcode);

#endif