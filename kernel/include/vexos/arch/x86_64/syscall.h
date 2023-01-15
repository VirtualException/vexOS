#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <vlibc/stdint.h>

#define NSYSCALLS 3

typedef void* syscall_ptr;
extern syscall_ptr syscall_table[NSYSCALLS];

void syscall_setup();
extern void syscall_enable(uint32_t offset_low, uint32_t offset_high);

extern void syscall_entry_64();

extern void syscall(long int n, ...);

long int sys_debug0();
long int sys_debug1();
long int sys_debug2();

#endif