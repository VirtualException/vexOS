#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef __x86_64__
    #define ARCH "x86_64"
#else
    #error "Architecture unsupported"
#endif

#ifdef __DEBUG__
    #pragma GCC warning "Compiling in debug mode"
#endif

#define STR(d) #d
#define XSTR(d) STR(d)

#define GCCVER (XSTR(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__))

#define VERSION "0.9.58"
#define AUTHOR  "VirtualException"

#endif
