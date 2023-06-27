#ifndef _PCSPKR_H
#define _PCSPKR_H

#include <vexos/dev/pit.h>

#define PCSPKR_CONTROL_PORT 0x61
#define PCSPKR_OFF_MASK     0xFC

void beep(int freq);
void stop_beep(void);

#endif