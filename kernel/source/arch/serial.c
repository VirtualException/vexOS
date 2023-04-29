#include <vexos/lib/bool.h>

#include <vexos/arch/serial.h>
#include <vexos/arch/io.h>

int
serial_setup() {

    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(PORT + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT + 4, 0x0F);

    serial_print("COM1 Serial working! (maybe it was already up)\n");

    return 0;
}

int
serial_is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

void
serial_write(char c) {

    while (serial_is_transmit_empty() == 0);

    outb(PORT, c);

    /* New lines require a carriage return */
    if (c == '\n') serial_write('\r');

    return;
}

void
serial_print(char* str) {

    for (size_t i = 0; str[i] != '\0'; i++) {
        serial_write(str[i]);
    }

    return;
}