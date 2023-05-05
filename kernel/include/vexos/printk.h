#ifndef _PRINTK_H
#define _PRINTK_H

#include <vexos/lib/vargs.h>

#define KERN_LOG        "\1"    /* Just treat message as log info*/
#define KERN_TLOG       "\2"    /* Add time headding to the log info*/

#define KERN_LOG_ASCII  '\1'
#define KERN_TLOG_ASCII '\2'

/* As ANSI Escape Codes are fucked up, i make my own implementation */

#define KERN_TERM_ESC               "\x1b"  /* Escape Code */
    #define KERN_TERM_ESC_ASCII     '\x1b'

#define KERN_TERM_OSC               "]"     /* Sequence start */
    #define KERN_TERM_OSC_ASCII     ']'

#define KERN_TERM_ESC_OSC           "\x1b]" /* Sequence Header */

#define KERN_TERM_END               "\x17"  /* Sequence End */
    #define KERN_TERM_END_ASCII     '\x17'

#define KERN_TERM_SEP               ";"     /* Separator */
    #define KERN_TERM_SEP_ASCII     ';'

#define KERN_TERM_COL_FG            "F"     /* Foreground color */
    #define KERN_TERM_COL_FG_ASCII  'F'

#define KERN_TERM_COL_BG            "B"     /* Background color */
    #define KERN_TERM_COL_BG_ASCII  'B'

#define KERN_TERM_COL_RST           "R"     /* Reset color */
    #define KERN_TERM_COL_RST_ASCII 'R'

#define KERN_TERM_FG(r, g, b)       /* "\x1b]F;{r};{g};{b}\x17" */ \
                                    KERN_TERM_ESC_OSC KERN_TERM_COL_FG \
                                    KERN_TERM_SEP #r KERN_TERM_SEP #g KERN_TERM_SEP #b KERN_TERM_END

#define KERN_TERM_BG(r, g, b)       /* "\x1b]G;{r};{g};{b}\x17" */ \
                                    KERN_TERM_ESC_OSC KERN_TERM_COL_BG \
                                    KERN_TERM_SEP #r KERN_TERM_SEP #g KERN_TERM_SEP #b KERN_TERM_END


int vsprintk(char *str, const char *fmt, va_list vargs);
int sprintk(char *str, const char *fmt, ...);

int vprintk(const char* fmt, va_list vargs);
int printk(const char* fmt, ...);

int putsk(const char* str);
int putchark(char c);

#endif