#include <vexos/printk.h>
#include <vexos/time.h>

#include <vexos/lib/macros.h>
#include <vexos/lib/bool.h>

#include <vexos/cpu/io.h>
#include <vexos/iobus/pic.h>


void
pic_setup() {

    printk(KERN_TLOG "Setting up PIC (w/o devices)... ");

    IRQ_OFF;

    pic_remap(0x20, 0x28);

    IRQ_ON;

    printk(KERN_LOG "[DONE]\n");

    return;
}

void
pic_remap(uint8_t pic1, uint8_t pic2) {

	uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, pic1);
    io_wait();
    outb(PIC2_DATA, pic2);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
    io_wait();

    return;
}

void
pic_mask(uint8_t irq) {

    uint16_t port;
    uint8_t value;
 
    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) | (1 << irq);
    outb(port, value);
    io_wait();

    return;
}

void
pic_unmask(uint8_t irq) {

    uint16_t port;
    uint8_t value;
 
    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
    io_wait();

    return;
}

void
pic_send_eoi(uint8_t irq) {

    if (irq >= 8) outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);

    return;
}
