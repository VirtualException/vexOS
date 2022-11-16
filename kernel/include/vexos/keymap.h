#ifndef _KEYMAP_H
#define _KEYMAP_H

#include <libc/stdbool.h>

char ps2ascii(int scancode, bool shift);
int get_kbd_input(char* c, uint8_t* kcode);

#endif