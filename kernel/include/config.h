#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef __x86_64__
    #define __ARCH__ "x86_64"
#else
    #error "Architecture unsupported"
#endif

#ifdef __DEBUG__
    #pragma GCC warning "Compiling in debug mode"
#endif

#define __BUILDVER__    "0.9.60"

#endif
