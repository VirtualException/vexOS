#ifndef _PS2_H
#define _PS2_H

#include <libc/types.h>
#include <kernel/io.h>

#define PS2_IO_CONTROL_PORT 0x60
#define PS2_EX_CONTROL_PORT 0x64

enum PS2_Keycodes {

#define PS2_Rel_Offset 0x80

    PS2_Null,

    PS2_Esc_Pressed         = 0x01,     PS2_Esc_Released        = PS2_Esc_Pressed       + PS2_Rel_Offset,

    PS2_Backspace_Pressed   = 0x0E,     PS2_Backspace_Released  = PS2_Backspace_Pressed + PS2_Rel_Offset,
    PS2_Tab_Pressed         = 0x0F,     PS2_Tab_Released        = PS2_Tab_Pressed       + PS2_Rel_Offset,

    PS2_Enter_Pressed       = 0x1C,     PS2_Enter_Released      = PS2_Enter_Pressed     + PS2_Rel_Offset,

    PS2_Shift_Pressed       = 0x2A,     PS2_Shift_Released      = PS2_Shift_Pressed     + PS2_Rel_Offset,

    PS2_Up_Pressed          = 0x48,     PS2_Up_Released         = PS2_Up_Pressed        + PS2_Rel_Offset,
    PS2_Left_Pressed        = 0x4B,     PS2_Left_Released       = PS2_Left_Pressed      + PS2_Rel_Offset,
    PS2_Right_Pressed       = 0x4D,     PS2_Right_Released      = PS2_Right_Pressed     + PS2_Rel_Offset,
    PS2_Down_Pressed        = 0x50,     PS2_Down_Released       = PS2_Down_Pressed      + PS2_Rel_Offset,


};

extern BYTE ps2_mouse_cycle;

extern SBYTE ps2_mouse_byte[4];
extern SBYTE ps2_mouse_dx;
extern SBYTE ps2_mouse_dy;

void ps2_mouse_handler();
void ps2_mouse_wait(BYTE t);
void ps2_mouse_write(BYTE data);
BYTE ps2_mouse_read();
void ps2_mouse_init();
void ps2_mouse_disable();

#endif