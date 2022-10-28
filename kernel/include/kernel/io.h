#ifndef _IO_H
#define _IO_H

unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);

unsigned int inportd(unsigned char port);
void outportd(unsigned short port, unsigned short data);

#endif