#ifndef TERM_H
#define TERM_H

#define PREVENT_WRITES_TO_VMEM 0

#include "../../font.h"

#include <libc/stdbool.h>

#include <vexos/kinfo.h>
#include <vexos/vinfo.h>
#include <vexos/video.h>

#define RGBCOL(r, g, b)     ((color_t) {b, g, r})
#define COL2PIXEL(color)    ((pixel_t) {(color).b, (color).g, (color).r, 0})

#define M_RESX 1920
#define M_RESY 1080

#define C_WDTH FONT_WDTH
#define C_HGHT FONT_HGHT

#define M_COLS (M_RESX / C_WDTH)
#define M_ROWS (M_RESY / C_HGHT)

#define TAB_SIZE 4

#define VTTS_N      1
#define VTTS_KLOG   0

typedef struct _vtt vtt;

typedef void (*VttClear)        (vtt* term);
typedef void (*VttNewline)      (vtt* term);
typedef void (*VttTab)          (vtt* term);
typedef void (*VttDelete)       (vtt* term);
typedef void (*VttScroll)       (vtt* term, uint32_t lines);
typedef void (*VttForward)      (vtt* term);
typedef void (*VttBackward)     (vtt* term);
typedef void (*VttSetCurPos)    (vtt* term, uint32_t x, uint32_t y);
typedef void (*VttSetCur)       (vtt* term, bool state);
typedef void (*VttSetFgCol)     (vtt* term, uint8_t r, uint8_t g, uint8_t b);
typedef void (*VttSetBgCol)     (vtt* term, uint8_t r, uint8_t g, uint8_t b);
typedef void (*VttResetCol)     (vtt* term);

typedef struct {

    char    c;
    color_t fg;
    color_t bg;

} tchar_t;

typedef struct _vtt {

    uint32_t cols;
    uint32_t rows;

    uint32_t curx;
    uint32_t cury;

    color_t col_fg;
    color_t col_bg;

    tchar_t defchar;

    bool cursor;
    bool blink;

    VttClear        clear;
    VttNewline      newline;
    VttTab          tab;
    VttDelete       delete;
    VttScroll       scroll;
    VttForward      forward;
    VttBackward     backward;
    VttSetCurPos    setcurpos;
    VttSetCur       setcur;
    VttSetFgCol     setfgcol;
    VttSetBgCol     setbgcol;
    VttResetCol     resetcol;

    tchar_t termbuff[M_COLS * M_ROWS];

} vtt;

void vtt_setup(kinfo_t* kinfo, uint32_t cols, uint32_t rows);
void vtt_init_term(vtt* term, uint32_t cols, uint32_t rows);
void vtt_switch_to(size_t vtt_num);

int vtt_handle();

void vtt_clear(vtt* term);
void vtt_newline(vtt* term);
void vtt_tab(vtt* term);
void vtt_delete(vtt* term);
void vtt_scroll(vtt* term, uint32_t lines);
void vtt_forward(vtt* term);
void vtt_backward(vtt* term);
void vtt_getcurpos(vtt* term, uint32_t* x, uint32_t* y);
void vtt_setcurpos(vtt* term, uint32_t x, uint32_t y);
void vtt_setcur(vtt* term, bool state);
void vtt_resetcol(vtt* term);
void vtt_setfgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b);
void vtt_setbgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b);

void vtt_renderterm();
void vtt_drawcur(vtt* term, uint32_t x, uint32_t y);

void vtt_putchar(vtt* term, char c);

#endif