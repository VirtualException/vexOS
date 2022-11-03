#include <kernel/ps2.h>
#include <kernel/keymap.h>

// This array is intended to transform every PRESS keycode into the correspondent ASCII character
// If 0 is the value returned, any ascii character is avaiable for that key or combination

static char PS2_KEYMAP_US[0x3A] = {
    '\0',
    '\0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\0',
    '\0',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\0',
    '\0',
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    '\0',
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    '\0',
    '*',
    '\0',
    ' ',
};

char ps2ascii(int scancode, bool shift) {

    char c;

    if (scancode <= 0x3A) {

        c = PS2_KEYMAP_US[scancode];

        if (c > 96 && c < 123 && shift) c -= 32;

    }
    else c = '\0';

    return c;
}