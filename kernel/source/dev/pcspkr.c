#include <vexos/lib/types.h>
#include <vexos/arch/io.h>
#include <vexos/dev/pcspkr.h>
#include <vexos/lib/extra_types.h>

void
beep(int freq) {

    DWORD div;
    BYTE tmp;

    // Set the PIT to the desired frequency

    div = PIT_FREQ / freq;
    outportb(PIT_CONTROL_PORT_3, 0xB6);
    outportb(PIT_CONTROL_PORT_2, (BYTE)(div));
    outportb(PIT_CONTROL_PORT_2, (BYTE)(div >> 8));

    // Play the sound using the PC speaker

    tmp = inportb(PCSPKR_CONTROL_PORT);
    if (tmp != (tmp | 3)) {
        outportb(PCSPKR_CONTROL_PORT, tmp | 3);
    }
}

void
stop_beep(void) {

    // Stop the speaker

    BYTE tmp = inportb(PCSPKR_CONTROL_PORT) & PCSPKR_OFF_MASK;
    outportb(PCSPKR_CONTROL_PORT, tmp);
}