/* VTT - VirTual Terminal */

#ifndef _VTT_H
#define _VTT_H

#include <vexos/graphics.h>

#include <vexos/lib/bool.h>

#undef _FONTDATA
#include "../../font/font.h"

#define M_RESX 1920
#define M_RESY 1080

#define M_COLS (M_RESX / CHAR_WDTH)
#define M_ROWS (M_RESY / CHAR_HGHT)

#define TAB_SIZE 8

#define VTTS_N      3
#define VTTS_MAX    (VTTS_N - 1)
#define VTTS_KLOG   0

/* X,Y TO LINEAR. Convert (x, y), with y <= w into a 1D value */
#define XY2L(x, y, w) ((x) + ((y) * (w)))

typedef struct _vtt vtt;

typedef void (*vtt_clear_func)      (vtt* term);
typedef void (*vtt_newline_func)    (vtt* term);
typedef void (*vtt_tab_func)        (vtt* term);
typedef void (*vtt_delete_func)     (vtt* term);
typedef void (*vtt_scroll_func)     (vtt* term, uint32_t lines);
typedef void (*vtt_forward_func)    (vtt* term);
typedef void (*vtt_backward_func)   (vtt* term);
typedef void (*vtt_setcurpos_func)  (vtt* term, uint32_t x, uint32_t y);
typedef void (*vtt_setcur_func)     (vtt* term, bool state);
typedef void (*vtt_setfgcol_func)   (vtt* term, uint8_t r, uint8_t g, uint8_t b);
typedef void (*vtt_setbgcol_func)   (vtt* term, uint8_t r, uint8_t g, uint8_t b);
typedef void (*vtt_resetcol_func)   (vtt* term);

typedef int (*vtt_handle_func)      (vtt* term);

typedef struct {

    char    c;
    color_t fg;
    color_t bg;

    bool updated;

} tchar_t;

typedef struct _vtt_vtable {

    vtt_clear_func      clear;
    vtt_newline_func    newline;
    vtt_tab_func        tab;
    vtt_delete_func     delete;
    vtt_scroll_func     scroll;
    vtt_forward_func    forward;
    vtt_backward_func   backward;
    vtt_setcurpos_func  setcurpos;
    vtt_setcur_func     setcur;
    vtt_setfgcol_func   setfgcol;
    vtt_setbgcol_func   setbgcol;
    vtt_resetcol_func   resetcol;

} vtt_vtable;

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

    bool enabled;

    int escape;

    vtt_vtable *f;
    vtt_handle_func     handle;

    tchar_t termbuff[M_COLS * M_ROWS];

} vtt;


extern vtt vtts[VTTS_N];
extern size_t vttcurrterm;

/* Provisional shell-like handle */

int vtt_handle(void);

/* VTT generic functions */

void vtt_setup();
void vtt_init_term(vtt* term, uint32_t cols, uint32_t rows);
void vtt_set_handle(size_t vtt_num, vtt_handle_func handle);
void vtt_switch_to(size_t vtt_num);
void vtt_update_set(vtt* term);

/* Per-VTT character-related functions */

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

/* printf lasts words */

void vtt_putchar(vtt* term, char c);
void vtt_putchar_at(vtt* term, char c, uint32_t x , uint32_t y);

/* Render stuff */

void vtt_renderterm(void);
void vtt_drawcur(vtt* term, uint32_t x, uint32_t y);
void vtt_drawtchar(uint32_t x, uint32_t y, tchar_t* tc);

#endif
