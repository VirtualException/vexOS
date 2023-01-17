#ifndef _PS2_H
#define _PS2_H

#include <vexos/lib/types.h>
#include <vexos/arch/x86_64/io.h>
#include <vexos/lib/extra_types.h>

#define PS2_IO_CONTROL_PORT 0x60
#define PS2_EX_CONTROL_PORT 0x64

#define PS2_REL_OFFSET 0x80
/* ##Cool!## */
#define DEF_PS2_KEY(name)   PS2_##name##_Pressed    = __COUNTER__, \
                            PS2_##name##_Released   = PS2_##name##_Pressed + PS2_REL_OFFSET,

enum PS2_Keycodes {

    DEF_PS2_KEY(Null)
    DEF_PS2_KEY(Esc)
    DEF_PS2_KEY(1)
    DEF_PS2_KEY(2)
    DEF_PS2_KEY(3)
    DEF_PS2_KEY(4)
    DEF_PS2_KEY(5)
    DEF_PS2_KEY(6)
    DEF_PS2_KEY(7)
    DEF_PS2_KEY(8)
    DEF_PS2_KEY(9)
    DEF_PS2_KEY(0)
    DEF_PS2_KEY(Minus)
    DEF_PS2_KEY(Equal)
    DEF_PS2_KEY(Backspace)
    DEF_PS2_KEY(Tab)
    DEF_PS2_KEY(Q)
    DEF_PS2_KEY(W)
    DEF_PS2_KEY(E)
    DEF_PS2_KEY(R)
    DEF_PS2_KEY(T)
    DEF_PS2_KEY(Y)
    DEF_PS2_KEY(U)
    DEF_PS2_KEY(I)
    DEF_PS2_KEY(O)
    DEF_PS2_KEY(P)
    DEF_PS2_KEY(OpenBracket)
    DEF_PS2_KEY(CloseBracket)
    DEF_PS2_KEY(Enter)
    DEF_PS2_KEY(LeftControl)
    DEF_PS2_KEY(A)
    DEF_PS2_KEY(S)
    DEF_PS2_KEY(D)
    DEF_PS2_KEY(F)
    DEF_PS2_KEY(G)
    DEF_PS2_KEY(H)
    DEF_PS2_KEY(J)
    DEF_PS2_KEY(K)
    DEF_PS2_KEY(L)
    DEF_PS2_KEY(SemiColon)
    DEF_PS2_KEY(SingleQuote)
    DEF_PS2_KEY(BackTick)
    DEF_PS2_KEY(LeftShift)
    DEF_PS2_KEY(BackSlash)
    DEF_PS2_KEY(Z)
    DEF_PS2_KEY(X)
    DEF_PS2_KEY(C)
    DEF_PS2_KEY(V)
    DEF_PS2_KEY(B)
    DEF_PS2_KEY(N)
    DEF_PS2_KEY(M)
    DEF_PS2_KEY(Comma)
    DEF_PS2_KEY(Dot)
    DEF_PS2_KEY(Slash)
    DEF_PS2_KEY(RightShift)
    DEF_PS2_KEY(K_Asterisk)
    DEF_PS2_KEY(LeftAlt)
    DEF_PS2_KEY(Space)
    DEF_PS2_KEY(CapsLock)
    DEF_PS2_KEY(F1)
    DEF_PS2_KEY(F2)
    DEF_PS2_KEY(F3)
    DEF_PS2_KEY(F4)
    DEF_PS2_KEY(F5)
    DEF_PS2_KEY(F6)
    DEF_PS2_KEY(F7)
    DEF_PS2_KEY(F8)
    DEF_PS2_KEY(F9)
    DEF_PS2_KEY(F10)
    DEF_PS2_KEY(NumLock)
    DEF_PS2_KEY(ScrollLock)
    DEF_PS2_KEY(K_7)
    DEF_PS2_KEY(K_8)
    DEF_PS2_KEY(K_9)
    DEF_PS2_KEY(K_Minus)
    DEF_PS2_KEY(K_4)
    DEF_PS2_KEY(K_5)
    DEF_PS2_KEY(K_6)
    DEF_PS2_KEY(K_Plus)
    DEF_PS2_KEY(K_1)
    DEF_PS2_KEY(K_2)
    DEF_PS2_KEY(K_3)
    DEF_PS2_KEY(K_0)
    DEF_PS2_KEY(K_Dot)
    DEF_PS2_KEY(Undefined1)
    DEF_PS2_KEY(Undefined2)
    DEF_PS2_KEY(Undefined3)
    DEF_PS2_KEY(F11)
    DEF_PS2_KEY(F12)

    /* TODO: Media keys support*/

};

extern BYTE ps2_mouse_cycle;

extern SBYTE ps2_mouse_byte[4];
extern SBYTE ps2_mouse_dx;
extern SBYTE ps2_mouse_dy;

void ps2_mouse_handler(void);
void ps2_mouse_wait(BYTE t);
void ps2_mouse_write(BYTE data);
BYTE ps2_mouse_read(void);
void ps2_mouse_init(void);
void ps2_mouse_disable(void);

#endif