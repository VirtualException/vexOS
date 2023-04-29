#ifndef _TERM_H
#define _TERM_H

#include <vexos/info/video.h>

#include <vexos/lib/bool.h>

#undef  _FONTDATA
#include "../../ter10x16.h"

#define M_RESX 1920
#define M_RESY 1080

#define C_WDTH FONT_WDTH
#define C_HGHT FONT_HGHT

#define M_COLS (M_RESX / C_WDTH)
#define M_ROWS (M_RESY / C_HGHT)

#define TAB_SIZE 8

#define VTTS_N      3
#define VTTS_MAX    (VTTS_N-1)
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

    bool updated;

} tchar_t;

typedef struct _vtt {

    uint32_t cols;
    uint32_t rows;

    uint32_t curx;
    uint32_t cury;

    tchar_t defchar;

    color_t col_fg;
    color_t col_bg;

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

extern vtt vtts[VTTS_N];
extern size_t vttcurrterm;

int vtt_handle(void);

void vtt_setup(uint32_t cols, uint32_t rows);
void vtt_init_term(vtt* term, uint32_t cols, uint32_t rows);
void vtt_switch_to(size_t vtt_num);
void vtt_update_set(vtt* term);
void vtt_handle_key();

void vtt_clear(vtt* term);
void vtt_newline(vtt* term);
void vtt_tab(vtt* term);
void vtt_delete(vtt* term);
void vtt_scroll(vtt* term, uint32_t lines);
void vtt_forward(vtt* term);
void vtt_backward(vtt* term);
void vtt_setcurpos(vtt* term, uint32_t x, uint32_t y);
void vtt_setcur(vtt* term, bool state);
void vtt_resetcol(vtt* term);
void vtt_setfgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b);
void vtt_setbgcol(vtt* term, uint8_t r, uint8_t g, uint8_t b);

void vtt_renderterm(void);
void vtt_drawcur(vtt* term, uint32_t x, uint32_t y);
void vtt_drawtchar(uint32_t x, uint32_t y, tchar_t* tc);

void vtt_putchar(vtt* term, char c);

#endif