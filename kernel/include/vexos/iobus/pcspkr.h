#ifndef _PCSPKR_H
#define _PCSPKR_H

#include <vexos/iobus/pit.h>

#define PCSPKR_CONTROL_PORT 0x61
#define PCSPKR_OFF_MASK     0xFC

void pcspkr_beep(int freq);
void pcspkr_stop();

#endif
