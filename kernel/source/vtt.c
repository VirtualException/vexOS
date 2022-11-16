#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <libc/vargs.h>
#include <libc/string.h>

#include <kernel/vtt.h>
#include <kernel/draw.h>
#include <kernel/ps2.h>
#include <kernel/keymap.h>

#define UID(x, y)           ((x) + ((y) * RESX))
#define UIDC(x, y)          ((x) + ((y) * COLS))
#define UIDw(x, y, w)       ((x) + ((y) * (w)))

// Thanks claudipunchi for macro magic!
#define GET_FONT_PIXEL_INDEX(c, x, y)   (UIDw(\
                                        ((((c)%FONT_BMP_WDTH)) * FONT_WDTH),\
                                        ((((c)-(((c)%FONT_BMP_WDTH)))/FONT_BMP_WDTH) * FONT_HGHT),\
                                        FONT_BMP_WDTH * FONT_WDTH)\
                                        + UIDw(x, y, FONT_BMP_WDTH * FONT_WDTH))

uint32_t RESX;
uint32_t RESY;

pixel_t* font;
pixel_t* bbuff;

size_t vttcurrterm;

vtt vtts[VTTS_N];

void
vtt_setup(kinfo_t* kinfo, uint32_t cols, uint32_t rows) {

    RESX = kinfo->video_info.x_res;
    RESY = kinfo->video_info.y_res;

    if (cols == 0 || cols > RESX / C_WDTH) {
        cols = M_COLS;
    }
    if (rows == 0 || rows > RESY / C_HGHT) {
        rows = M_ROWS;
    }

    bbuff = (pixel_t*) kinfo->video_info.vmem;

    font = kinfo->font_bitmap;

    for (size_t i = 0; i < VTTS_N; i++) {
        vtt_init_term(&vtts[i], cols, rows);
    }

    memset((void*) kinfo->video_info.vmem, kinfo->video_info.vmem_size, 0x00);

    vtt_switch_to(VTTS_KLOG);

    return;
}

void
vtt_init_term(vtt* term, uint32_t cols, uint32_t rows) {

    term->cols      = cols;
    term->rows      = rows;
    term->curx      = 0;
    term->cury      = 0;
    term->cursor    = false;
    term->blink     = true;
    term->col_fg    = RGBCOL(0x43, 0xf0, 0x83);
    term->col_bg    = RGBCOL(0x05, 0x13, 0x0a);
    term->defchar   = (tchar_t) {'\0', term->col_fg, term->col_bg};

    memset(term->termbuff, M_COLS * M_ROWS * sizeof(tchar_t), 0x0);

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

    term->clear(term);

    return;
}

void
vtt_clear(vtt* term) {

    for (size_t y = 0; y < term->rows; y++) {
        for (size_t x = 0; x < term->cols; x++) {
            term->termbuff[UIDw(x, y, term->cols)] = term->defchar;
        }
    }

    return;
}

void
vtt_switch_to(size_t vtt_num) {

    vttcurrterm = vtt_num;

    return;

}

int
vtt_handle() {

    char c          = 0;
    uint8_t kcode   = 0;
    int ret         = 0;

    get_kbd_input(&c, &kcode);

    if (!kcode) return ret;
    if (c) putchar(c);

    vtt* term = &vtts[vttcurrterm];

    switch (kcode) {
    case PS2_F1_Pressed:
        vtt_switch_to(0);
        break;

    case PS2_F2_Pressed:
        vtt_switch_to(1);
        break;

    case PS2_F3_Pressed:
        vtt_switch_to(2);
        break;

    case PS2_F4_Pressed:
        vtt_switch_to(3);
        break;

    case PS2_Tab_Pressed:
        term->tab(term);
        break;

    case PS2_Enter_Pressed:
        term->newline(term);
        break;

    case PS2_Backspace_Pressed:
        term->delete(term);
        break;

    case PS2_Esc_Released:
        ret = 1;

    default:
        break;
    }

    return ret;
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

    for (size_t i = 0; i < TAB_SIZE; i++) {
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
            }
        }
    }

    for (size_t x = 0; x < term->cols; x++) {
        term->termbuff[UIDw(x, term->rows-1, term->cols)] = (tchar_t) {'\0', term->col_fg, term->col_bg};
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

            drawchar(x * C_WDTH, y * C_HGHT, &term->termbuff[UIDw(x, y, term->cols)], bbuff);

            if(x == term->curx && y == term->cury && term->blink && (term->cursor = !term->cursor)) {
                vtt_drawcur(term, x * C_WDTH, y * C_HGHT);
            }
        }
    }

    return;
}

void
vtt_drawcur(vtt* term, uint x, uint y) {

    drawchar(x, y, &(tchar_t) {CURSOR, term->col_fg, term->col_bg}, bbuff);

    return;
}

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

        default:
            term->termbuff[UIDw(term->curx, term->cury, term->cols)] = (tchar_t) { c, term->col_fg, term->col_bg };
            term->forward(term);

            break;
    }

    return;
}

/* stdio implementation (very cranky and creepy for now) */

int
putchar(char c) {

    vtt_putchar(&vtts[vttcurrterm], c);

    return c;

}

int
putchark(char c) {

    vtt_putchar(&vtts[VTTS_KLOG], c);

    return c;

}

/* draw implementation */

void
drawpixel(uint32_t x, uint32_t y, pixel_t* bbuff, color_t col) {

    pixel_t* pixel = &bbuff[UID(x, y)];

    pixel->r = col.r;
    pixel->g = col.g;
    pixel->b = col.b;

}

void
drawchar(uint32_t x, uint32_t y, tchar_t* tc, pixel_t* bbuff) {

    for (size_t dy = 0; dy < C_HGHT; dy++) {
        for (size_t dx = 0; dx < C_WDTH; dx++) {

            uint64_t index = GET_FONT_PIXEL_INDEX(tc->c, dx, dy);
            pixel_t* pixel = &bbuff[UID(x + dx, y + dy)];

            *pixel = COL2PIXEL((font[index].r == 0xFF) ? tc->fg : tc->bg);

        }
    }

    return;
}