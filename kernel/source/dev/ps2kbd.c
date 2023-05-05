#include <vexos/dev/ps2kbd.h>
#include <vexos/arch/io.h>
#include <vexos/lib/macros.h>
#include <vexos/printk.h>

/*
 * This array is intended to transform every PRESS keycode (everything before caps lock,
 * wich may be printable) into the correspondent ASCII character.
 * If 0 is the value returned, any ascii character is avaiable for that key or combination
 */

char PS2_KEYMAP_US[0x3A][2] =
{
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
    {'w', 'W'},
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

uint8_t     scancode        = 0;
uint8_t     oldscancode     = 0;
/*uint32_t    timeout         = KBD_TIMEOUT;*/
/*uint32_t    first_timeout   = KBD_FIRST_TIMEOUT;*/

bool shift = false;

void
ps2kbd_setup() {

    scancode = 0;
    oldscancode = 0;
    shift = 0;

    return;

}

char
ps2kbd_ps2ascii(int this_scancode, bool this_shift) {

    char c = 0;

    if (this_scancode <= 0x3A) {

        c = PS2_KEYMAP_US[this_scancode][this_shift];

    }
    else c = '\0';

    return c;
}

int
ps2kbd_get_input(char* c, uint8_t* kcode) {

    oldscancode = scancode;
    scancode    = inportb(PS2_IO_CONTROL_PORT);

    /* Repeated key handler */

//    if (oldscancode == scancode) {
//
//        /* Repeat rate check */
//
//        if (first_timeout)  return first_timeout--;
//        else if (timeout)   return timeout--;
//
//        timeout = KBD_TIMEOUT;
//
//    } else first_timeout = KBD_FIRST_TIMEOUT;


    *kcode  = scancode;
    *c      = '\0';

    switch (*kcode = scancode) {

    case PS2_LeftShift_Pressed:
    case PS2_RightShift_Pressed:
        shift = true;
        break;

    case PS2_LeftShift_Released:
    case PS2_RightShift_Released:
        shift = false;
        break;

    case PS2_CapsLock_Released:
        shift = !shift;
        break;

    default:
        *c = ps2kbd_ps2ascii(scancode, shift);
        break;
    }

    return 0;
}