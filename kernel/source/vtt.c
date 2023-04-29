#include <vexos/vtt.h>
#include <vexos/printk.h>
#include <vexos/draw.h>
#include <vexos/info/kinfo.h>
#include <vexos/dev/ps2def.h>
#include <vexos/dev/keyboard.h>
#include <vexos/arch/syscall.h>
#include <vexos/memory.h>
#include <vexos/lib/string.h>
#include <vexos/lib/vargs.h>


#define UIDw(x, y, w) ((x) + ((y) * (w)))


vtt vtts[VTTS_N] = { 0 };
size_t vttcurrterm;

uint32_t RESX;
uint32_t RESY;

pixel_t* video_buff;

char c = 0;
uint8_t kcode = 0;

int ret;


void
vtt_setup(uint32_t cols, uint32_t rows) {

/* TODO: Fix resolutions */

    RESX = kinfo->video_info.x_res;
    RESY = kinfo->video_info.y_res;

    if (cols == 0 || cols > RESX / C_WDTH) {
        cols = RESX / C_WDTH;
    }
    if (rows == 0 || rows > RESY / C_HGHT) {
        rows = RESY / C_HGHT;
    }

    video_buff = (pixel_t*) kinfo->video_info.vmem;

    for (size_t i = 0; i < VTTS_N; i++) {
        vtt_init_term(&vtts[i], cols, rows);
    }

    memset((void*) kinfo->video_info.vmem, kinfo->video_info.vmem_size, 0x00);

    c       = '\0';
    kcode   = PS2_Null_Pressed;
    ret     = 0;

    vtt_switch_to(VTTS_KLOG);

    printk(KERN_LOG "VTT succesfully initializated\n");

    return;
}

void
vtt_init_term(vtt* term, uint32_t cols, uint32_t rows) {

/* 0x40, 0xF0, 0x50 - 0x00, 0x15, 0x05 */

    term->cols      = cols;
    term->rows      = rows;
    term->curx      = 0;
    term->cury      = 0;
    term->cursor    = false;
    term->blink     = true;
    term->defchar   = (tchar_t) { '\0', RGBCOL(0xaa, 0xaa, 0xaa), RGBCOL(0x00, 0x00, 0x00), true};
    term->col_fg    = term->defchar.fg;
    term->col_bg    = term->defchar.bg;

    term->clear     = vtt_clear;
    term->newline   = vtt_newline;
    term->tab       = vtt_tab;
    term->delete    = vtt_delete;
    term->scroll    = vtt_scroll;
    term->forward   = vtt_forward;
    term->backward  = vtt_backward;
    term->setcurpos = vtt_setcurpos;
    term->setcur    = vtt_setcur;
    term->resetcol  = vtt_resetcol;
    term->setfgcol  = vtt_setfgcol;
    term->setbgcol  = vtt_setbgcol;

    memset(term->termbuff, M_COLS * M_ROWS * sizeof(tchar_t), 0x0);

    term->clear(term);

    return;
}

void
vtt_clear(vtt* term) {

    for (size_t i = 0; i < term->rows * term->cols; i++) {
        term->termbuff[i] = term->defchar;
    }

    term->curx = 0;
    term->cury = 0;

    return;
}

void
vtt_switch_to(size_t vtt_num) {

    vttcurrterm = vtt_num;

    vtt_update_set(&vtts[vttcurrterm]);

    return;

}

void
vtt_update_set(vtt* term) {

    for (size_t i = 0; i < term->rows * term->cols; i++) {
        term->termbuff[i].updated = true;
    }

    return;
}

int
vtt_handle() {

    vtt* term = &vtts[vttcurrterm];

    term->cursor = !term->cursor;

    if (!kcode) return ret;
    if (c) vtt_putchar(term, c);

    switch (kcode) {

    case PS2_F1_Pressed ... PS2_F1_Pressed + VTTS_MAX:
        vtt_switch_to(kcode - PS2_F1_Pressed);
        printk(KERN_LOG "Switched to vtt %d\n", kcode - PS2_F1_Pressed);
        break;

    case PS2_Tab_Pressed:
        term->tab(term);
        break;

    case PS2_Enter_Pressed:
        /**/
        term->newline(term);
        break;

    case PS2_Backspace_Pressed:
        term->delete(term);
        break;

    case PS2_K_4_Pressed:
        term->backward(term);
        break;

    case PS2_K_6_Pressed:
        term->forward(term);
        break;

    case PS2_F9_Pressed:
        term->clear(term);
        break;

    case PS2_Esc_Released:
        ret = 1;
        break;

    case PS2_X_Pressed:
        break;

    default:
        break;
    }

    c       = '\0';
    kcode   = PS2_Null_Pressed;

    return ret;
}

void
vtt_handle_key() {

    kbd_get_input(&c, &kcode);

    return;
}

void
vtt_newline(vtt* term) {

    if (term->cury >= term->rows-1) {
        term->scroll(term, 1);
    }
    else term->cury++;

    term->curx = 0;

    return;
}

void
vtt_tab(vtt* term) {

    size_t n = TAB_SIZE - ((term->curx + 1) % TAB_SIZE);

    if (n == TAB_SIZE) return;

    for (size_t i = 0; i < n; i++) {
        term->forward(term);
    }

    return;
}

void
vtt_delete(vtt* term) {

    term->backward(term);

    term->termbuff[UIDw(term->curx, term->cury, term->cols)] = term->defchar;

    return;
}

void
vtt_scroll(vtt* term, uint32_t lines) {

    for (size_t l = 0; l < lines; l++) {
        for (size_t y = 0; y < term->rows-1; y++) {
            for (size_t x = 0; x < term->cols; x++) {
                term->termbuff[UIDw(x, y, term->cols)] = term->termbuff[UIDw(x, y+1, term->cols)];
                term->termbuff[UIDw(x, y, term->cols)].updated = true;
            }
        }
    }

    for (size_t x = 0; x < term->cols; x++) {
        term->termbuff[UIDw(x, term->rows-1, term->cols)] = (tchar_t) {'\0', term->col_fg, term->col_bg, 1};
    }

    return;
}

void
vtt_forward(vtt* term) {

    if (term->curx >= term->cols-1) {
        term->newline(term);
        term->curx = 0;
    }
    else term->curx++;

    if (term->cury >= term->rows) {
        term->scroll(term, 1);
        term->cury--;
    }

    return;
}

void
vtt_backward(vtt* term) {

    if (term->curx < 1) {
        if (term->cury > 1) {
            term->cury--;
            term->curx = term->cols-1;
        }
    }
    else term->curx--;

}

void
vtt_setcurpos(vtt* term, uint32_t  x, uint32_t y) {

    if (x > term->cols || y > term->rows) {
        return;
    }

    term->curx = x;
    term->cury = y;

    return;
}

void
vtt_setcur(vtt* term, bool state) {

    term->blink = (term->cursor = state);

    return;
}

void
vtt_setfgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b) {

    term->col_fg = RGBCOL(r, g, b);

    return;
}

void
vtt_setbgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b) {

    term->col_bg = RGBCOL(r, g, b);

    return;
}

void
vtt_resetcol(vtt* term) {

    term->col_fg = term->defchar.fg;
    term->col_bg = term->defchar.bg;

    return;
}

void
vtt_renderterm() {

    vtt* term = &vtts[vttcurrterm];

    for (size_t y = 0; y < term->rows; y++) {
        for (size_t x = 0; x < term->cols; x++) {

            tchar_t* tc = &term->termbuff[UIDw(x, y, term->cols)];

IRQ_OFF;
            if (tc->updated == true) {
                vtt_drawtchar(x * C_WDTH, y * C_HGHT, tc);
            }

            if (x == term->curx && y == term->cury && term->blink && !term->cursor) {
                vtt_drawcur(term, x * C_WDTH, y * C_HGHT);
            }
IRQ_ON;

        }
    }

    return;
}

void
vtt_drawcur(vtt* term, uint32_t x, uint32_t y) {

    vtt_drawtchar(x, y, &(tchar_t) { CURSOR, term->col_fg, term->col_bg, true });
    term->termbuff[UIDw(term->curx, term->cury, term->cols)].updated = true;

    return;
}

void
vtt_drawtchar(uint32_t x, uint32_t y, tchar_t* tc) {

    drawchar(x, y, tc->c, tc->fg, tc->bg, &kinfo->font, &kinfo->video_info);
    tc->updated = false;

    return;
}

int handle_escape = 0;

void
vtt_putchar(vtt* term, char c) {

    switch (c) {

        case '\n':
            term->newline(term);
            break;

        case '\t':
            term->tab(term);
            break;

        case '\0':
            break;

        case KERN_TERM_ESC_ASCII:
            handle_escape = c;
            break;

        default:
            /* !!! */
            term->termbuff[UIDw(term->curx, term->cury, term->cols)] = (tchar_t) { c, term->col_fg, term->col_bg, true };
            term->forward(term);

            break;
    }

    vtt_renderterm(); /* ...meh */

    return;
}