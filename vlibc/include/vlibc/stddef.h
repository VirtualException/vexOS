#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL ((void*) 0)

#include <vlibc/stdint.h>

typedef uint64_t            size_t;
typedef int64_t             ssize_t;

typedef uint16_t            wchar_t;

typedef uint64_t            ulong;
typedef uint16_t            ushort;
typedef uint32_t            uint;

#endif