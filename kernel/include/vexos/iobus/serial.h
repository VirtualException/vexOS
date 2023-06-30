#ifndef _SERIAL_H
#define _SERIAL_H

#define COM_PORT 0x3F8 // COM1

void serial_setup();
void serial_write(char c);
void serial_print(char* str);

#endif
