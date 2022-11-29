#include <vexos/video.h>

int
swapbuff(video_info_t* vinfo, pixel_t* buff) {

    size_t          len = vinfo->vmem_size;
    uint8_t*        d   = (uint8_t*) vinfo->vmem;
    uint8_t*        s   = (uint8_t*) buff;

    while (len--) {
        if (*d != *s) *d = *s;
        d++;
        s++;
    }

    return EXIT_SUCCESS;
}