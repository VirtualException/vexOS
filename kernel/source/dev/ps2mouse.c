//Mouse.inc by SANiK
//License: Use as you wish, except to cause damage

#include <vexos/printk.h>

#include <vexos/dev/ps2mouse.h>
#include <vexos/arch/io.h>

BYTE  ps2_mouse_cycle=0;
SBYTE ps2_mouse_byte[3];
SBYTE ps2_mouse_x=0;
SBYTE ps2_mouse_y=0;

//Mouse functions
void ps2_mouse_handler(__unused void* a_r) //struct regs *a_r (not used but just there)
{
  printk("<ps2mouse>");
  switch(ps2_mouse_cycle)
  {
    case 0:
      ps2_mouse_byte[0]=inportb(0x60);
      ps2_mouse_cycle++;
      break;
    case 1:
      ps2_mouse_byte[1]=inportb(0x60);
      ps2_mouse_cycle++;
      break;
    case 2:
      ps2_mouse_byte[2]=inportb(0x60);
      ps2_mouse_x=ps2_mouse_byte[1];
      ps2_mouse_y=ps2_mouse_byte[2];
      ps2_mouse_cycle=0;
      break;
  }

  //pic_send_eoi(12);
}

void ps2_mouse_wait(BYTE a_type) //unsigned char
{
  DWORD _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inportb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

void ps2_mouse_write(BYTE data) //unsigned char
{
  //Wait to be able to send a command
  ps2_mouse_wait(1);
  //Tell the mouse we are sending a command
  outportb(0x64, 0xD4);
  //Wait for the final part
  ps2_mouse_wait(1);
  //Finally write
  outportb(0x60, data);
}

BYTE ps2_mouse_read()
{
  //Get's response from mouse
  ps2_mouse_wait(0);
  return inportb(0x60);
}

void ps2_mouse_init()
{
  BYTE _status;  //unsigned char

  //Enable the auxiliary mouse device
  ps2_mouse_wait(1);
  outportb(0x64, 0xA8);

  //Enable the interrupts
  ps2_mouse_wait(1);
  outportb(0x64, 0x20);
  ps2_mouse_wait(0);
  _status=(inportb(0x60) | 2);
  ps2_mouse_wait(1);
  outportb(0x64, 0x60);
  ps2_mouse_wait(1);
  outportb(0x60, _status);

  //Tell the mouse to use default settings
  ps2_mouse_write(0xF6);
  ps2_mouse_read();  //Acknowledge

  //Enable the mouse
  ps2_mouse_write(0xF4);
  ps2_mouse_read();  //Acknowledge

  //Setup the mouse handler

}