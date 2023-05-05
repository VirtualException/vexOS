#ifndef _PS2KBD_H
#define _PS2KBD_H

#include <vexos/lib/types.h>
#include <vexos/lib/bool.h>

#include <vexos/dev/ps2keys.h>

#define PS2_IO_CONTROL_PORT 0x60
#define PS2_EX_CONTROL_PORT 0x64

void    ps2kbd_setup();
char    ps2kbd_ps2ascii(int scancode, bool shift);
int     ps2kbd_get_input(char* c, uint8_t* kcode);

#endif