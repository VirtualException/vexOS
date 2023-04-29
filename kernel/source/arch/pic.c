#include <vexos/printk.h>
#include <vexos/lib/macros.h>
#include <vexos/lib/bool.h>

#include <vexos/arch/io.h>
#include <vexos/dev/pic.h>

int
pic_setup() {

    printk(KERN_LOG "Setting up PIC...\n");

IRQ_OFF;

    pic_remap(0x20, 0x28);

    outb(PIC1_DATA, ~PIC_KEYBOARD_IRQ);
    outb(PIC2_DATA, ~PIC_PS2MOUSE_IRQ);
    outb(PIC2_DATA, ~0b1111111);

IRQ_ON;

    printk(KERN_LOG "Testing keyboard: ");
    INTCALL(0x21);
    printk("\n");

    printk(KERN_LOG "PIC set up correctly\n");

    return 0;
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

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    return;
}

void
pic_send_eoi(uint8_t irq) {

    if (irq > 7) outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);

    return;
}