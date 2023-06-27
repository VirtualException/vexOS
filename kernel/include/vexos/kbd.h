#ifndef _KBD_H
#define _KBD_H

#include <vexos/lib/types.h>

#define KEY_BUFFER_SIZE 16
#define INPUT_BUFFER_SIZE 16

#define KBD_REL_OFFSET 0x80
/* ##Cool!## */
#define DEF_KBD(name)   KBD_##name##_Pressed    = __COUNTER__, \
                        KBD_##name##_Released   = KBD_##name##_Pressed + KBD_REL_OFFSET

enum KeyDefs {

    DEF_KBD(Null),
    DEF_KBD(Esc),
    DEF_KBD(1),
    DEF_KBD(2),
    DEF_KBD(3),
    DEF_KBD(4),
    DEF_KBD(5),
    DEF_KBD(6),
    DEF_KBD(7),
    DEF_KBD(8),
    DEF_KBD(9),
    DEF_KBD(0),
    DEF_KBD(Minus),
    DEF_KBD(Equal),
    DEF_KBD(Backspace),
    DEF_KBD(Tab),
    DEF_KBD(Q),
    DEF_KBD(W),
    DEF_KBD(E),
    DEF_KBD(R),
    DEF_KBD(T),
    DEF_KBD(Y),
    DEF_KBD(U),
    DEF_KBD(I),
    DEF_KBD(O),
    DEF_KBD(P),
    DEF_KBD(OpenBracket),
    DEF_KBD(CloseBracket),
    DEF_KBD(Enter),
    DEF_KBD(LeftControl),
    DEF_KBD(A),
    DEF_KBD(S),
    DEF_KBD(D),
    DEF_KBD(F),
    DEF_KBD(G),
    DEF_KBD(H),
    DEF_KBD(J),
    DEF_KBD(K),
    DEF_KBD(L),
    DEF_KBD(SemiColon),
    DEF_KBD(SingleQuote),
    DEF_KBD(BackTick),
    DEF_KBD(LeftShift),
    DEF_KBD(BackSlash),
    DEF_KBD(Z),
    DEF_KBD(X),
    DEF_KBD(C),
    DEF_KBD(V),
    DEF_KBD(B),
    DEF_KBD(N),
    DEF_KBD(M),
    DEF_KBD(Comma),
    DEF_KBD(Dot),
    DEF_KBD(Slash),
    DEF_KBD(RightShift),
    DEF_KBD(K_Asterisk),
    DEF_KBD(LeftAlt),
    DEF_KBD(Space),
    DEF_KBD(CapsLock),
    DEF_KBD(F1),
    DEF_KBD(F2),
    DEF_KBD(F3),
    DEF_KBD(F4),
    DEF_KBD(F5),
    DEF_KBD(F6),
    DEF_KBD(F7),
    DEF_KBD(F8),
    DEF_KBD(F9),
    DEF_KBD(F10),
    DEF_KBD(NumLock),
    DEF_KBD(ScrollLock),
    DEF_KBD(K_7),
    DEF_KBD(K_8_Up),
    DEF_KBD(K_9),
    DEF_KBD(K_Minus),
    DEF_KBD(K_4_Left),
    DEF_KBD(K_5),
    DEF_KBD(K_6_Right),
    DEF_KBD(K_Plus),
    DEF_KBD(K_1),
    DEF_KBD(K_2_Down),
    DEF_KBD(K_3),
    DEF_KBD(K_0),
    DEF_KBD(K_Dot),
    DEF_KBD(Undefined1),
    DEF_KBD(Undefined2),
    DEF_KBD(Undefined3),
    DEF_KBD(F11),
    DEF_KBD(F12),

    DEF_KBD(COUNT),

    /* TODO: Media keys support*/

};

void        kbd_key_buffer_push(uint32_t kcode);
void        kbd_key_buffer_pop();
uint32_t    kbd_getkey();

void        kbd_input_buffer_push(char c);
void        kbd_input_buffer_pop();
char        kbd_getchar();

void        kbd_init();

#endif