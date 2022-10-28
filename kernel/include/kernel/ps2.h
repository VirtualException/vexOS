#ifndef _PS2_H
#define _PS2_H

#include <libc/types.h>
#include <kernel/io.h>

#define PS2_IO_CONTROL_PORT 0x60
#define PS2_EX_CONTROL_PORT 0x64

enum PS2_Keycodes {

    PS2_Null,

    // Press                        // Release (+0x80)

    PS2_Esc_Pressed     = 0x01,     PS2_Esc_Released    = PS2_Esc_Pressed   + 0x80,

    PS2_Up_Pressed      = 0x48,     PS2_Up_Released     = PS2_Up_Pressed    + 0x80,
    PS2_Left_Pressed    = 0x4B,     PS2_Left_Released   = PS2_Left_Pressed  + 0x80,
    PS2_Right_Pressed   = 0x4D,     PS2_Right_Released  = PS2_Right_Pressed + 0x80,
    PS2_Down_Pressed    = 0x50,     PS2_Down_Released   = PS2_Down_Pressed  + 0x80,

};

extern BYTE mouse_cycle;
extern SBYTE mouse_byte[4];
extern SBYTE mouse_dx;
extern SBYTE mouse_dy;

void ps2_mouse_handler();
void ps2_mouse_wait(BYTE t);
void ps2_mouse_write(BYTE data);
BYTE ps2_mouse_read();
void ps2_mouse_init();
void ps2_mouse_disable();

#endif