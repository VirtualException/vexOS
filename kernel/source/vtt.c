#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <libc/vargs.h>
#include <libc/mem.h>

#include <kernel/vtt.h>
#include <kernel/draw.h>

#define UID(x, y)       ((x) + ((y) * RESX))
#define UIDC(x, y)      ((x) + ((y) * COLS))
#define UID_w(x, y, w)  ((x) + ((y) * (w)))

// Max resolution
#define M_RESX 1920
#define M_RESY 1080

// Character width
#define C_WDTH 10
#define C_HGHT 16

// Thanks claudipunchi for macro magic!
#define GET_FONT_PIXEL_INDEX(c, x, y)   (UID_w(\
                                        ((((c)%FONT_BMP_WDTH)) * FONT_WDTH),\
                                        ((((c)-(((c)%FONT_BMP_WDTH)))/FONT_BMP_WDTH) * FONT_HGHT),\
                                        FONT_BMP_WDTH * FONT_WDTH)\
                                        +\
                                        UID_w(x, y, FONT_BMP_WDTH * FONT_WDTH))

// Max terminal dimensions
#define M_COLS (unsigned)(M_RESX / C_WDTH)
#define M_ROWS (unsigned)(M_RESY / C_HGHT)

// Current resolution
uint32_t RESX;
uint32_t RESY;

// Current terminal dimensions
uint32_t COLS;
uint32_t ROWS;

// Current cursor position
uint32_t CURX;
uint32_t CURY;

// Current color
color_t col_fg;
color_t col_bg;

bool    cursor;

pixel_t* font;

tchar_t termbuff[M_COLS * M_ROWS];

tchar_t voidchar;


void
init_terminal(uint32_t x_res, uint32_t y_res, pixel_t* font_bitmap) {

    RESX = x_res;
    RESY = y_res;

    COLS = RESX / C_WDTH;
    ROWS = RESY / C_HGHT;

    CURX = 0;
    CURY = 0;

    font = font_bitmap;

    memset(termbuff, M_COLS * M_ROWS * sizeof(tchar_t), 0x0);

    memset(&voidchar, sizeof(tchar_t), 0x0);

    resetcolor();

    cursor = true;

    return;
}

void
newline() {

    if (CURY > ROWS-1) {
        scroll(1);
    }
    else CURY++;

    CURX = 0;

    return;
}

void
scroll(uint32_t lines) {

    for (size_t l = 0; l < lines; l++) {
        for (size_t y = 1; y < ROWS; y++) {
            for (size_t x = 0; x < COLS; x++) {
                termbuff[UIDC(x, y-1)] = termbuff[UIDC(x, y)];
            }
        }
    }

    /*//???????
    for (size_t i = 0; i < COLS; i++) {
        termbuff[UIDC(i, ROWS-1)] = voidchar;
    }
    for (size_t i = 0; i < COLS; i++) {
        termbuff[UIDC(i, ROWS)] = voidchar;
    }*/

    CURY--;

    return;
}

void
resetcolor() {
    col_fg = (color_t) { 180, 180, 180 };
    col_bg = (color_t) { 0, 0, 0 };
    return;
}

void
setfgcolor(uint8_t r, uint8_t g, uint8_t b) {
    col_fg = (color_t) { b, g, r};
    return;
}

void
setbgcolor(uint8_t r, uint8_t g, uint8_t b) {
    col_bg = (color_t) { b, g, r};
    return;
}

void
renderterm(pixel_t* bbuff) {

    for (size_t y = 0; y < ROWS; y++) {
        for (size_t x = 0; x < COLS; x++) {

            drawchar(x * C_WDTH, y * C_HGHT, &termbuff[UIDC(x, y)], bbuff);

            if(x == CURX && y == CURY) {
                rendercur(x * C_WDTH, y * C_HGHT, bbuff);
            }
        }
    }

    return;
}

void
drawchar(uint32_t x, uint32_t y, tchar_t* c, pixel_t* bbuff) {

    for (size_t dy = 0; dy < C_HGHT; dy++) {
        for (size_t dx = 0; dx < C_WDTH; dx++) {

            pixel_t* pixel = &bbuff[UID(x + dx, y + dy)];
            uint64_t index = GET_FONT_PIXEL_INDEX(c->c, dx, dy);

            if (font[index].r == 0xFF) {
                *pixel = *(pixel_t*) &c->fg;
            }
            else *pixel = *(pixel_t*) &c->bg;

        }
    }

    return;
}

void
rendercur(uint x, uint y, pixel_t* bbuff) {

    cursor = !cursor;

    if (cursor) {
        return;
    }

    for (size_t dy = 0; dy < C_HGHT; dy++) {
        for (size_t dx = 0; dx < C_WDTH; dx++) {

            pixel_t* pixel = &bbuff[UID(x + dx, y + dy)];
            uint64_t index = GET_FONT_PIXEL_INDEX(CURSOR, dx, dy);

            if (font[index].r == 0xFF) {
                *pixel = *(pixel_t*) &col_fg;
            }

        }
    }

    return;
}

int
vprintf(const char* fmt, va_list vargs) {

    char buff[1048] = { 0 };

    for (size_t i = 0; fmt[i] != '\0'; i++) {

        switch (fmt[i]) {

        case '\n':

            newline();
            break;

        case '\t':

            printf("    ");
            break;

        case '%':

            switch (fmt[i+1]) {

            case '%':

                putchar('%');
                break;

            case 'c':
            case 'C':

                putchar(va_arg(vargs));

                break;

            case 'd':
            case 'D':

                itoa(va_arg(vargs), buff);
                printf(buff);

                break;

            default:

                break;

            }

            i++;
            break;

        default:
            putchar(fmt[i]);
            break;
        }
    }

    return 0;

}

int
printf(const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    vprintf(fmt, vargs);

    va_end(vargs);

    return EXIT_SUCCESS;
}

int
printfat(unsigned int x, unsigned int y, const char* fmt, ...) {

    va_list vargs;
    va_start(vargs);

    if (x > COLS || y > ROWS) {
        return -1;
    }

    CURX = x;
    CURY = y;

    vprintf(fmt, vargs);

    va_end(vargs);

    return 0;
}

int
putchar(char c) {

    if (CURX >= COLS) {
        newline();
    }

    termbuff[UIDC(CURX, CURY)] = (tchar_t) { .c = c, .fg = col_fg, .bg = col_bg };

    CURX++;

    return EXIT_SUCCESS;
}