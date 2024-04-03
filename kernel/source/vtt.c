/* VTT - VirTual Terminal */

#include <vexos/vtt.h>
#include <vexos/cmd.h>
#include <vexos/printk.h>
#include <vexos/time.h>
#include <vexos/bootinfo.h>

#include <vexos/lib/memory.h>
#include <vexos/lib/string.h>
#include <vexos/lib/vargs.h>

#include <vexos/cpu/interrupts.h>

#include <vexos/iobus/ps2/ps2kbd.h>
#include <vexos/iobus/pit.h>

#define DEFAULT_COL_FG  RGBCOL(0xCC, 0xCC, 0xCC)
#define DEFAULT_COL_BG  RGBCOL(0x00, 0x00, 0x00)

//#define DEFAULT_COL_FG  RGBCOL(0x40, 0xF0, 0x50) 
//#define DEFAULT_COL_BG  RGBCOL(0x00, 0x15, 0x05)

/**
 * Pseudo-ANSI Sequential Escape Parser
 *
 * Each value indicates what the handler expects.
 * For now, only handles the H escape code (cursor to home position).
*/

enum {
    ESCAPE_NONE,
    ESCAPE_CSI,
    ESCAPE_ARG,

    ESCAPE_MAX,
};

vtt     vtts[VTTS_N];
size_t  vttcurrterm;

uint32_t RESX;
uint32_t RESY;

pixel_t* vmem;


void
vtt_setup() {

    RESX = bootinfo.vinfo.x_res;
    RESY = bootinfo.vinfo.y_res;

    uint32_t cols = RESX / CHAR_WDTH;
    uint32_t rows = RESY / CHAR_HGHT;

    vmem = (pixel_t*) bootinfo.vinfo.vmem;

    for (size_t i = 0; i < VTTS_N; i++) {
        vtt_init_term(&vtts[i], cols, rows);
    }

    memset((void*)bootinfo.vinfo.vmem, bootinfo.vinfo.vmem_size, 0x00);

    vtt_switch_to(VTTS_KLOG);

    printk(KERN_TLOG "VTT succesfully initializated\n");

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
    term->escape    = ESCAPE_NONE;
    term->defchar   = (tchar_t) { '\0', DEFAULT_COL_FG, DEFAULT_COL_BG, true };
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

    term->handle    = cmd;

    memset(term->termbuff, M_COLS * M_ROWS * sizeof(tchar_t), 0x0);

    term->enabled   = true;

    term->clear(term);

    return;
}

void vtt_set_handle(size_t vtt_num, vtt_handle_func handle) {

    vtt* term = &vtts[vtt_num];
    term->handle = handle;

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

    term->cursor = ((time_ms_boot() / 500) % 2 == 0);

    vtt_renderterm();

    return term->handle(term);
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

    term->termbuff[XY2L(term->curx, term->cury, term->cols)] = term->defchar;

    return;
}

void
vtt_scroll(vtt* term, uint32_t lines) {

    for (size_t l = 0; l < lines; l++) {
        for (size_t y = 0; y < term->rows-1; y++) {
            for (size_t x = 0; x < term->cols; x++) {
                term->termbuff[XY2L(x, y, term->cols)] = term->termbuff[XY2L(x, y+1, term->cols)];
                term->termbuff[XY2L(x, y, term->cols)].updated = true;
            }
        }
    }

    for (size_t x = 0; x < term->cols; x++) {
        term->termbuff[XY2L(x, term->rows-1, term->cols)] = term->defchar;
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

            tchar_t* tc = &term->termbuff[XY2L(x, y, term->cols)];

            if (x == term->curx && y == term->cury && term->blink && term->cursor) {
                vtt_drawcur(term, x * CHAR_WDTH, y * CHAR_HGHT);
            }
            else if (tc->updated == true) {
                vtt_drawtchar(x * CHAR_WDTH, y * CHAR_HGHT, tc);
            }

        }
    }

    return;
}

void
vtt_drawcur(vtt* term, uint32_t x, uint32_t y) {

    vtt_drawtchar(x, y, &(tchar_t) { ' ', term->col_bg, term->col_fg, true });
    term->termbuff[XY2L(term->curx, term->cury, term->cols)].updated = true;

    return;
}

void
vtt_drawtchar(uint32_t x, uint32_t y, tchar_t* tc) {

    graphics_drawchar(x, y, tc->c, tc->fg, tc->bg, &bootinfo.font, &bootinfo.vinfo);

    tc->updated = false;

    return;
}

void
vtt_putchar(vtt* term, char c) {

    if (!term->enabled) {
        return;
    }

    switch (term->escape) {

    case ESCAPE_NONE:
        break;

    case ESCAPE_CSI:

        if (c == '[')
            term->escape++;
        else 
            term->escape = 0;

        return;

    case ESCAPE_ARG:

        if (c == 'H') {
            term->curx = 0;
            term->cury = 0;
        }

        term->escape = ESCAPE_NONE;

        printk(KERN_TLOG "PANSI Handle\n");

        return;

    default:
        break;

    }

    switch (c) {

    case '\0':
        break;

    case '\e':
        term->escape = ESCAPE_CSI;
        break;

    case '\n':
        term->newline(term);
        break;

    case '\t':
        term->tab(term);
        break;

    /* ... */

    default:

        /* Really important code: Write formatted char into the terminal buffer */

        term->termbuff[XY2L(term->curx, term->cury, term->cols)] =
            (tchar_t) { c, term->col_fg, term->col_bg, true };
        term->forward(term);

        vtt_renderterm(); /* ...meh */

        break;
    }

    return;
}

void
vtt_putchar_at(vtt* term, char c, uint32_t x, uint32_t y) {

    uint32_t old_curx = term->curx;
    uint32_t old_cury = term->cury;

    term->curx = x;
    term->cury = y;

    vtt_putchar(term, c);

    term->curx = old_curx;
    term->cury = old_cury;

}
