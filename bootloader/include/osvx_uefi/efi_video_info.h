#ifndef _VIDEO_INFO_H
#define _VIDEO_INFO_H

#include <efi/efi.h>

typedef struct {

    char R;
    char G;
    char B;

    char _Reserved;

} PIXEL;

typedef struct {

    UINT32 XRes;
    UINT32 YRes;

    UINT64 VMem;
    UINT64 VMem_Size;

} VIDEO_INFO;

#endif