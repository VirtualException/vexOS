#include <vexos/kprintf.h>
#include <vexos/pointer.h>
#include <vexos/lib/macros.h>

#include <vexos/cpu/interrupts.h>
#include <vexos/cpu/io.h>

#include <vexos/iobus/ps2/ps2.h>
#include <vexos/iobus/ps2/ps2mouse.h>
#include <vexos/iobus/pic.h>

#define PS2Leftbutton   0b00000001
#define PS2Middlebutton 0b00000010
#define PS2Rightbutton  0b00000100
#define PS2XSign        0b00010000
#define PS2YSign        0b00100000
#define PS2XOverflow    0b01000000
#define PS2YOverflow    0b10000000

/* Based on Mouse.inc by SANiK */

void
ps2mouse_setup() {

    // Enable the auxiliary mouse device
    ps2_wait(1);
    outportb(0x64, 0xA8);

    ps2_write(0xFF);

    // Enable the interrupts
    ps2_wait(1);
    outportb(0x64, 0x20);
    ps2_wait(0);
    uint8_t status = (inportb(0x60) | 2);
    ps2_wait(1);
    outportb(0x64, 0x60);
    ps2_wait(1);
    outportb(0x60, status);

    // Tell the mouse to use default settings
    ps2_write(0xF6);
    ps2_read();

    //Enable the mouse
    ps2_write(0xF4);
    ps2_read();

IRQ_OFF;

    pic_unmask(PIC_CASCADE_IRQ);
    pic_unmask(PIC_PS2MOUSE_IRQ);

IRQ_ON;

    return;
}

INTERRUPT(irq_ps2mouse) {

    IRQ_OFF;

    uint8_t ps2mouse_data[3] = { 0 };
    uint8_t ps2mouse_cycle = 0;

    ps2mouse_packet mouse_data;

    while (1) {

        switch(ps2mouse_cycle) {

            case 0:

                ps2mouse_data[0] = ps2_read();
                ps2mouse_cycle = 1;

                break;

            case 1:

                ps2mouse_data[1] = ps2_read();
                ps2mouse_cycle = 2;

                break;

            case 2:

                ps2mouse_data[2] = ps2_read();

                ps2mouse_procdata(ps2mouse_data, &mouse_data);
                pointer_handle_mouse(&mouse_data);

                ps2mouse_cycle = 0;

                pic_send_eoi(PIC_PS2MOUSE_IRQ);

                IRQ_ON;

                return;
        }

    }

    return;
}

void
ps2mouse_procdata(uint8_t data[3], ps2mouse_packet* mouse_data) {

    bool xNegative = 0, yNegative = 0, xOverflow = 0, yOverflow = 0;

        if (data[0] & PS2XSign){
            xNegative = true;
        }else xNegative = false;

        if (data[0] & PS2YSign){
            yNegative = true;
        }else yNegative = false;

        if (data[0] & PS2XOverflow){
            xOverflow = true;
        }else xOverflow = false;

        if (data[0] & PS2YOverflow){
            yOverflow = true;
        }else yOverflow = false;

        if (!xNegative){
            mouse_data->dx = data[1];
            if (xOverflow){
                mouse_data->dx += 255;
            }
        } else
        {
            data[1] = 256 - data[1];
            mouse_data->dy = data[1];
            if (xOverflow){
                mouse_data->dy = 255;
            }
        }

        if (!yNegative){
            mouse_data->dy = data[2];
            if (yOverflow){
                mouse_data->dy = 255;
            }
        } else
        {
            data[2] = 256 - data[2];
            mouse_data->dy = -data[2];
            if (yOverflow){
                mouse_data->dy = 255;
            }
        }

    return;
}
