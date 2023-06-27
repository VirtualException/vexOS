#ifndef _PS2MOUSE_H
#define _PS2MOUSE_H

#include <vexos/lib/bool.h>
#include <vexos/lib/types.h>

typedef struct _ps2mouse_packet {

    int16_t dx;
    int16_t dy;

    uint8_t left;
    uint8_t right;
    uint8_t middle;

    uint8_t reserved;

} ps2mouse_packet;


void ps2mouse_setup();
void ps2mouse_procdata(uint8_t data[3], ps2mouse_packet* mouse_data);

#endif