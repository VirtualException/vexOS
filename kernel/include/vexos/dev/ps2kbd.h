#ifndef _PS2KBD_H
#define _PS2KBD_H

#include <vexos/lib/types.h>
#include <vexos/lib/bool.h>

void    ps2kbd_setup();
char    ps2kbd_ps2ascii(uint32_t scancode, bool shift);

#endif