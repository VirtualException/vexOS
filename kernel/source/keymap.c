#include <kernel/ps2.h>
#include <kernel/keymap.h>

/* This array is intended to transform every PRESS keycode (everything before caps lock,
 * wich may be printable) into the correspondent ASCII character.
 * If 0 is the value returned, any ascii character is avaiable for that key or combination
 */

char PS2_KEYMAP_US[0x3A][2] = {

    {'\0'},
    {'\0'},

    {'1', '!'},
    {'2', '@'},
    {'3', '#'},
    {'4', '$'},
    {'5', '%'},
    {'6', '^'},
    {'7', '&'},
    {'8', '*'},
    {'9', '('},
    {'0', ')'},

    {'-', '_'},
    {'=', '+'},

    {'\0'},
    {'\0'},

    {'q', 'Q'},
    {'w', 'Q'},
    {'e', 'E'},
    {'r', 'R'},
    {'t', 'T'},
    {'y', 'Y'},
    {'u', 'U'},
    {'i', 'I'},
    {'o', 'O'},
    {'p', 'P'},
    {'[', '{'},
    {']', '}'},

    {'\0'},
    {'\0'},

    {'a', 'A'},
    {'s', 'S'},
    {'d', 'D'},
    {'f', 'F'},
    {'g', 'G'},
    {'h', 'H'},
    {'j', 'J'},
    {'k', 'K'},
    {'l', 'L'},

    {';', ':'},
    {'\'','\"'},
    {'`', '~'},

    {'\0'},

    {'\\','|'},

    {'z', 'Z'},
    {'x', 'X'},
    {'c', 'C'},
    {'v', 'V'},
    {'b', 'B'},
    {'n', 'N'},
    {'m', 'M'},

    {',', '<'},
    {'.', '>'},
    {'/', '?'},

    {'\0'},

    {'*', '*'},

    {'\0'},

    {' ', ' '}

};

uint8_t scancode    = 0;
uint8_t oldscancode = 0;
bool shift          = 0;

char ps2ascii(int scancode, bool shift) {

    char c = 0;

    if (scancode <= 0x3A) {

        c = PS2_KEYMAP_US[scancode][shift];

    }
    else c = '\0';

    return c;
}

int
get_kbd_input(char* c, uint8_t* kcode) {

    scancode = inportb(PS2_IO_CONTROL_PORT);

    if (oldscancode == scancode) {

        *kcode  = 0;
        *c      = 0;

        return 1;
    }

    oldscancode = scancode;

    *kcode = scancode;

    if (scancode == PS2_LeftShift_Pressed || scancode == PS2_RightShift_Pressed)        shift = true;
    else if (scancode == PS2_LeftShift_Released || scancode == PS2_RightShift_Released) shift = false;
    else {
        *c = ps2ascii(scancode, shift);
        return 0;
    }

    *c = 0;

    return 0;
}