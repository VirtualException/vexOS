#include <vexos/printk.h>
#include <vexos/kbd.h>

#include <vexos/lib/memory.h>
#include <vexos/lib/bool.h>

#include <vexos/iobus/pic.h>
#include <vexos/cpu/interrupts.h>

#include <vexos/iobus/ps2/ps2kbd.h>


uint32_t key_buffer[KEY_BUFFER_SIZE] = { 0 };
uint32_t key_buffer_offset = 0;

uint32_t input_buffer[INPUT_BUFFER_SIZE] = { 0 };
uint32_t input_buffer_offset = 0;

bool kbd_shift = 0;

void
kbd_key_buffer_push(uint32_t kcode) {

    switch (kcode) {

    case KBD_LeftShift_Pressed:
    case KBD_RightShift_Pressed:
        kbd_shift = true;
        break;

    case KBD_LeftShift_Released:
    case KBD_RightShift_Released:
        kbd_shift = false;
        break;

    case KBD_CapsLock_Released:
        kbd_shift = !kbd_shift;
        break;

    default:
        break;
    }

    char c = ps2kbd_ps2ascii(kcode, kbd_shift);

    if (c != '\0') {
        kbd_input_buffer_push(c);
    }

    if (key_buffer_offset < KEY_BUFFER_SIZE) {

        key_buffer[key_buffer_offset++] = kcode;

    }

    return;
}

void
kbd_key_buffer_pop() {

    if (key_buffer_offset > 0) {

        key_buffer[key_buffer_offset] = 0;
        key_buffer_offset -= 1;
        key_buffer[key_buffer_offset] = 0;

    }

    return;
}

uint32_t
kbd_getkey() {

    uint32_t key = 0;

    if (key_buffer_offset > 0) {

        key = key_buffer[key_buffer_offset-1];

    }

    kbd_key_buffer_pop();

    return key;
}

void
kbd_input_buffer_push(char c) {

    if (key_buffer_offset < INPUT_BUFFER_SIZE) {

        input_buffer[input_buffer_offset++] = c;

    }

    return;
}

void
kbd_input_buffer_pop() {

    if (input_buffer_offset > 0) {

        input_buffer[input_buffer_offset] = 0;
        input_buffer_offset -= 1;
        input_buffer[input_buffer_offset] = 0;

    }

    return;
}

char
kbd_getchar() {

    char c = 0;

    if (input_buffer_offset > 0) {

        c = input_buffer[input_buffer_offset-1];

    }

    kbd_input_buffer_pop();

    return c;
}

void
kbd_init() {

    memset(key_buffer, 0, KEY_BUFFER_SIZE);
    memset(input_buffer, 0, INPUT_BUFFER_SIZE);

    key_buffer_offset = 0;
    input_buffer_offset = 0;

    kbd_shift = false;

    return;
}
