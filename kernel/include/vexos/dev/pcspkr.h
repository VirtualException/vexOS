#ifndef _PCSPKR_H
#define _PCSPKR_H

#define PIT_FREQ            0x1234DE

#define PIT_CONTROL_PORT_0  0x40
#define PIT_CONTROL_PORT_1  0x41
#define PIT_CONTROL_PORT_2  0x42
#define PIT_CONTROL_PORT_3  0x43

#define PCSPKR_CONTROL_PORT 0x61
#define PCSPKR_OFF_MASK     0xFC

void beep(int freq);
void stop_beep(void);

#endif