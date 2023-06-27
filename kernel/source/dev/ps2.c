#include <vexos/dev/ps2.h>
#include <vexos/arch/io.h>

void
ps2_wait(uint8_t type) {

    uint32_t time_out = 100000; //unsigned int

    if (type == 0) {

        while (time_out--) {

            if ((inportb(0x64) & 1) == 1) return;
        }
        return;
    }
    else {

        while (time_out--) {
            if ((inportb(0x64) & 2) == 0) return;
        }
        return;
    }
}

void
ps2_write(uint8_t byte) {

    ps2_wait(1);
    outportb(0x64, 0xD4);

    ps2_wait(1);
    outportb(0x60, byte);

    return;
}

uint8_t
ps2_read() {

    ps2_wait(0);

    return inportb(0x60);
}