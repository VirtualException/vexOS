#include <vexos/ps2.h>

BYTE ps2_mouse_cycle = 0;

SBYTE ps2_mouse_byte[4];
SBYTE ps2_mouse_dx = 0;
SBYTE ps2_mouse_dy = 0;

//Mouse functions
void
ps2_mouse_handler() {

    switch(ps2_mouse_cycle) {

        case 0:
            ps2_mouse_byte[0] = inportb(PS2_IO_CONTROL_PORT);
            ps2_mouse_cycle++;
        break;

    case 1:
      ps2_mouse_byte[1] = inportb(PS2_IO_CONTROL_PORT);
      ps2_mouse_cycle++;
      break;

    case 2:
      ps2_mouse_byte[2] = inportb(PS2_IO_CONTROL_PORT);
      ps2_mouse_dx = ps2_mouse_byte[1];
      ps2_mouse_dy = ps2_mouse_byte[2];
      ps2_mouse_cycle = 0;
      break;
  }
}

void
ps2_mouse_wait(BYTE t) {

  DWORD _time_out = 100000;
  if(t == 0) {
    while(_time_out--) {
      if( (inportb(PS2_EX_CONTROL_PORT) & 1) == 1) {
        return;
      }
    }
    return;
  }
  else {
    while(_time_out--) {
      if( (inportb(PS2_EX_CONTROL_PORT) & 2) == 0) {
        return;
      }
    }
    return;
  }
}

void
ps2_mouse_write(BYTE data) {
    //Wait to be able to send a command
    ps2_mouse_wait(1);
    //Tell the mouse we are sending a command
    outportb(PS2_EX_CONTROL_PORT, 0xD4);
    //Wait for the final part
    ps2_mouse_wait(1);
    //Finally write
    outportb(PS2_IO_CONTROL_PORT, data);
}

BYTE
ps2_mouse_read() {
    //Get's response from mouse
    ps2_mouse_wait(0);
    return inportb(PS2_IO_CONTROL_PORT);
}

void
ps2_mouse_init() {

    BYTE _status;

    //Enable the auxiliary mouse device
    ps2_mouse_wait(1);
    outportb(PS2_EX_CONTROL_PORT, 0xA8);

    //Enable the interrupts
    ps2_mouse_wait(1);
    outportb(PS2_EX_CONTROL_PORT, 0x20);
    ps2_mouse_wait(0);
    _status = (inportb(PS2_IO_CONTROL_PORT) | 2);
    ps2_mouse_wait(1);
    outportb(PS2_EX_CONTROL_PORT, 0x60);
    ps2_mouse_wait(1);
    outportb(PS2_IO_CONTROL_PORT, _status);

    //Tell the mouse to use default settings
    ps2_mouse_write(0xF6);
    ps2_mouse_read();

    ps2_mouse_write(0xF4);
    ps2_mouse_read();
}

void
ps2_mouse_disable() {
    return;
}