#ifndef _STDINT_H
#define _STDINT_H

typedef signed char         int8_t;
typedef signed short int    int16_t;
typedef signed int          int32_t;
typedef signed long int     int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;

typedef unsigned long int   uintptr_t;

#include <vlibc/stddef.h>

#endif