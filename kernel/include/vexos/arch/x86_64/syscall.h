#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <vexos/lib/types.h>

#define NSYSCALLS 4

typedef void* syscall_ptr;

extern syscall_ptr syscall_table[NSYSCALLS];

uint64_t syscall_setup();

long int sys_debug0();
long int sys_debug1();
long int sys_debug2();
long int sys_debug3();

extern void syscall_entry_64();
extern void syscall(long int n, ...);

#endif