#ifndef _SHELL_H
#define _SHELL_H

#include <kernel/kinfo.h>

int vex_shell(KInfo* kinfo);
int event_key(char* c, uint8_t* eky);

#endif