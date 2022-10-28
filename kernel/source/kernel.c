#include <libc/stdio.h>         // Standard libraries
#include <libc/stdlib.h>        //
#include <libc/stdbool.h>       //
#include <libc/mem.h>           //

#include <kernel/vtt.h>         // Console

#include <kernel/draw.h>        // Drawing

#include <kernel/ps2.h>         // Keyboard-related
#include <kernel/keymap.h>      //

#include <kernel/kinfo.h>       // Kernel-realted
#include <kernel/video_info.h>  //

#define STOP    while(1)

int vtt_shell(KInfo* kinfo);
int events(char* c, int* event);

int
kmain(KInfo* kinfo) {

    srand((uint64_t) kinfo->back_buffer);

    init_terminal(kinfo->video_info.x_res, kinfo->video_info.y_res, kinfo->font_bitmap);

    printf("Hi! %c %c\nRunning a shitty kernel on x86_64\n\n", FONT_SMILE_BLACK, FONT_HEART_BLACK);

    for (size_t i = 0; i < 0x80; i++) {
        putchar(i);
    }

    setbgcolor(0x50, 0xC2, 0xF7);
    setfgcolor(0, 0, 0);

    printf("\n\nThe quick brown fox jumps over the lazy dog\n\n");

    resetcolor();

// ^  Pre-shell logs!!

    while (1) {

        uint8_t scancode = inportb(PS2_IO_CONTROL_PORT);

        printfat(0, 0, "%d    ", (uint64_t) scancode);

        renderterm((pixel_t*) kinfo->video_info.vmem);

    }


    //vtt_shell(kinfo);

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;

}

int
vtt_shell(KInfo* kinfo) {

    printf("Wellcome to the vttshell!\n");

    while (1) {

        char c;
        int event;

        events(&c, &event);

        switch (event) {
        case 1:
            break;

        case 2:
            break;

        default:
            break;
        }

        if(c == ';') return 0;

        renderterm((pixel_t*) kinfo->video_info.vmem); // Write directly to vmem, forget video buffering
        //swapbuff(&kinfo->video_info, kinfo->back_buffer);

    }

    return 0;
}

int
events(char* c, int* event) {

//Todo: event types, ps2shar conversions

    static uint8_t scancode;

    scancode = inportb(PS2_IO_CONTROL_PORT);

    *c = ps2ascii(scancode);

    *event = 0;

    return 0;

}