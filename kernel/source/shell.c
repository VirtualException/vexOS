#include <libc/stdio.h>
#include <libc/string.h>

#include <kernel/shell.h>
#include <kernel/vtt.h>
#include <kernel/ps2.h>
#include <kernel/keymap.h>

uint8_t scancode        = 0;
uint8_t lastscancode    = 0;

int
vex_shell(KInfo* kinfo) {

    printf("Wellcome to the vexshell!\n");

    char cmd[255] = { 0 };

    while (1) {

        char c;
        uint8_t event;

        event_key(&c, &event);

        if (c) {

            char c0[2] = { c, '\0' };
            strcat(cmd, c0);
            putchar(c);

        }

        switch (event) {

        case PS2_Esc_Pressed:
            return 0;
            break;

        case PS2_Enter_Pressed:
            newline();
            puts(cmd);
            newline();
            memset(cmd, 255, 0);
            puts("$ ");
            break;

        case PS2_Tab_Pressed:
            tab();

            break;

        case PS2_Backspace_Pressed:
            cmd[strlen(cmd)-1] = '\0';
            delete();
            break;

        default:
            break;
        }

        renderterm((pixel_t*) kinfo->video_info.vmem); // Write directly to vmem, forget video buffering
        //swapbuff(&kinfo->video_info, kinfo->back_buffer);

    }

    return 0;
}

int
event_key(char* c, uint8_t* eky) {

    static bool shift = false;

    scancode = inportb(PS2_IO_CONTROL_PORT);

    if (lastscancode == scancode) {

        *eky    = 0;
        *c      = 0;

        return 1;
    }

    lastscancode = scancode;

    *eky = scancode;

    if (scancode == PS2_Shift_Pressed)        shift = true;
    else if (scancode == PS2_Shift_Released)  shift = false;

    *c = ps2ascii(scancode, shift);

    return 0;
}