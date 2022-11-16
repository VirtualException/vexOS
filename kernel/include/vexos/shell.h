#ifndef _SHELL_H
#define _SHELL_H

#include <vexos/kinfo.h>
#include <vexos/vtt.h>

int vex_shell(kinfo_t* kinfo, vtt* term);
int eventskb(char* c, uint8_t* eky);
int execshellcmd(char* cmd);

#endif