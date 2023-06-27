#include <vexos/arch/io.h>

#define PIT_FREQ        0x1234DE    /* Random number */
#define PIT_TIMER_FREQ  1000        /* The PIT will fire 1000 times/second */

#define PIT_CONTROL_PORT_0 0x40
#define PIT_CONTROL_PORT_1 0x41
#define PIT_CONTROL_PORT_2 0x42
#define PIT_CONTROL_PORT_3 0x43

void pit_setup();
void pit_wait(uint64_t cs);