#include <libc/stdio.h>         // Standard libraries
#include <libc/stdlib.h>        //
#include <libc/stdbool.h>       //
#include <libc/string.h>        //

#include <kernel/vtt.h>         // Console

#include <kernel/shell.h>       // Shell

#include <kernel/draw.h>        // Drawing

#include <kernel/ps2.h>         // Keyboard-related
#include <kernel/keymap.h>      //

#include <kernel/kinfo.h>       // Kernel information

#define STOP    while(1)

#define VERSION 1.0
#define ARCH    "x86-64"


int
kmain(KInfo* kinfo) {

    srand((uint64_t) kinfo->back_buffer);

    init_terminal(kinfo->video_info.x_res, kinfo->video_info.y_res, kinfo->font_bitmap);

    printf("Welcome to vexOS! %c (%s, UEFI) %c\n[Build timestamp: %s]\n\n", FONT_TULI_LOGO, ARCH, FONT_SMILE_WHITE, __TIMESTAMP__);

    setbgcolor(0x50, 0xC2, 0xF7);
    setfgcolor(0, 0, 0);

    printf("The quick brown fox jumps over the lazy dog\n\n");

    resetcolor();

    vex_shell(kinfo);

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;
}