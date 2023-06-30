#ifndef _PS2_H
#define _PS2_H

#include <vexos/lib/types.h>

#define PS2_IO_PORT 0x60
#define PS2_EX_PORT 0x64

void ps2_wait(uint8_t type);
void ps2_write(uint8_t byte);
uint8_t ps2_read();

#endif