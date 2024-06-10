#include <vexos/cmd.h>
#include <vexos/kbd.h>
#include <vexos/printk.h>
#include <vexos/iobus/pcspkr.h>
#include <vexos/time.h>
#include <vexos/lib/macros.h>


int
cmd(vtt* term) {

    int ret = 0;

    uint8_t kcode = kbd_getkey();
    char c = kbd_getchar();

    if (!kcode) return ret;
    if (c) vtt_putchar(term, c);

    switch (kcode) {

    case KBD_F1_Pressed ... KBD_F1_Pressed + VTTS_MAX:
        vtt_switch_to(kcode - KBD_F1_Pressed);
        printk(KERN_TLOG "cmd: Switched to vtt %d\n", kcode - KBD_F1_Pressed);
        break;

    case KBD_Tab_Pressed:
        term->f->tab(term);
        break;

    case KBD_Enter_Pressed:

        //pcspkr_beep(430);
        //time_sleep(1000);
        //pcspkr_stop();

        term->f->newline(term);
        break;

    case KBD_Backspace_Pressed:

        term->f->delete(term);
        break;

    case KBD_K_8_Up_Pressed:
        term->cury--;
        break;

    case KBD_K_4_Left_Pressed:
        term->f->backward(term);
        break;

    case KBD_K_6_Right_Pressed:
        term->f->forward(term);
        break;

    case KBD_K_2_Down_Pressed:
        term->cury++;
        break;

    case KBD_F12_Pressed:
        term->f->clear(term);
        break;

    case KBD_Esc_Released:
        ret = 1;
        break;

    case KBD_K_Plus_Pressed:
        ASM("int3");
        break;

    default:
        break;
    }

    return ret;
}
