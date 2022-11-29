#ifndef _KEYMAP_H
#define _KEYMAP_H

#include <libc/stdbool.h>

void kbd_setup();
char kbd_ps2ascii(int scancode, bool shift);
int kbd_get_input(char* c, uint8_t* kcode);

#endif