#include <vexos/dev/ps2.h>
#include <vexos/dev/keyboard.h>
#include <vexos/lib/macros.h>
#include <vexos/printk.h>

/* This array is intended to transform every PRESS keycode (everything before caps lock,
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

uint8_t     scancode;
uint8_t     oldscancode;
uint32_t    timeout;
uint32_t    first_timeout;

bool shift;

void
kbd_setup(void) {

    printk(KERN_LOG "Setting up PS2 keyboard...\n");

    scancode    = 0;
    oldscancode = 0;
    shift       = 0;

    first_timeout   = KBD_FIRST_TIMEOUT;
    timeout         = KBD_TIMEOUT;

    printk(KERN_LOG "Keyboard setup correctly \n");

    return;
}

void 
kbd_reset_timeout(void) {
    timeout         = KBD_TIMEOUT;
}

char
kbd_ps2ascii(int _scancode, bool _shift) {

    char c = 0;

    if (_scancode <= 0x3A) {

        c = PS2_KEYMAP_US[_scancode][_shift];

    }
    else c = '\0';

    return c;
}

int
kbd_get_input(char* c, uint8_t* kcode) {

    oldscancode = scancode;
    scancode    = inportb(PS2_IO_CONTROL_PORT);

    *kcode      = PS2_Null_Pressed;
    *c          = '\0';

    /* Repeated key handler */

    if (oldscancode == scancode) {

        /* Repeat rate check */

        if (first_timeout)  return first_timeout--;
        else if (timeout)   return timeout--;

        timeout = KBD_TIMEOUT;

    } else first_timeout = KBD_FIRST_TIMEOUT;


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
        *c = kbd_ps2ascii(scancode, shift);
        break;
    }

    return 0;
}