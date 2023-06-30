#ifndef _POINTER_H
#define _POINTER_H

#include <vexos/lib/types.h>
#include <vexos/lib/bool.h>
#include <vexos/iobus/ps2/ps2mouse.h>

void pointer_handle_mouse(ps2mouse_packet* mouse_data);

#endif
