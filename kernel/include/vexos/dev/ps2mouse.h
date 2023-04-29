#include <vexos/lib/extra_types.h>
#include <vexos/lib/macros.h>

extern BYTE  ps2_mouse_cycle;
extern SBYTE ps2_mouse_byte[3];
extern SBYTE ps2_mouse_x;
extern SBYTE ps2_mouse_y;

void ps2_mouse_handler(__unused void* a_r);
void ps2_mouse_wait(BYTE a_type);
void ps2_mouse_write(BYTE data);
BYTE ps2_mouse_read(void);
void ps2_mouse_init(void);