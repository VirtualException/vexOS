#include <vexos/vtt.h>
#include <vexos/kprintf.h>
#include <vexos/kbd.h>
#include <vexos/lib/macros.h>

#include <vexos/dev/ps2.h>
#include <vexos/dev/ps2kbd.h>

#include <vexos/arch/io.h>
#include <vexos/arch/pic.h>
#include <vexos/arch/interrupts.h>

/*
 * This array is intended to transform every PRESS keycode (everything before
 * caps lock, wich may be printable) into the correspondent ASCII character.
 * If 0 is the value returned, there is no ascii character avaiable for that
 * key or key combination
 */

char KEYMAP_QWERTY_US[0x3A][2] = {

    "\0\0",
    "\0\0",

    "1!",
    "2@",
    "3#",
    "4$",
    "5%",
    "6^",
    "7&",
    "8*",
    "9(",
    "0)",
    "-_",
    "=+",

    "\0\0",
    "\0\0",

    "qQ",
    "wW",
    "eE",
    "rR",
    "tT",
    "yY",
    "uU",
    "iI",
    "oO",
    "pP",
    "[{",
    "]}",

    "\0\0",
    "\0\0",

    "aA",
    "sS",
    "dD",
    "fF",
    "gG",
    "hH",
    "jJ",
    "kK",
    "lL",

    ";:",
    "\'\"",
    "`~",

    "\0\0",

    "\\|",

    "zZ",
    "xX",
    "cC",
    "vV",
    "bB",
    "nN",
    "mM",

    ",<",
    ".>",
    "/?",

    "\0\0",

    "**",

    "\0\0",

    "  ",
};

void
ps2kbd_setup() {

    kprintf(KERN_TLOG "Setting up PS/2 Keyboard... ");

    IRQ_OFF;

    pic_unmask(PIC_PS2KBD_IRQ);

    IRQ_ON;

    kprintf(KERN_LOG "[DONE]\n");

    return;

}

char
ps2kbd_ps2ascii(uint32_t scancode, bool shift) {

    char c = 0;

    if (scancode <= 0x3A) {

        c = KEYMAP_QWERTY_US[scancode][shift];

    }
    else c = '\0';

    return c;
}

INTERRUPT(irq_ps2kbd) {

    IRQ_OFF;

    kprintf(KERN_TLOG "IRQ PS/2 Keyboard\n");

    uint32_t kcode = inportb(PS2_IO_PORT);

    kbd_key_buffer_push(kcode);

    pic_send_eoi(PIC_PS2KBD_IRQ);

    IRQ_ON;

    return;
}
