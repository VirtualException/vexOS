#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <vexos/lib/types.h>

#define SYSCALLS_N 4

typedef void* syscall_ptr;

uint64_t syscall_setup();

#define SYSCALL(name) long x64_syscall_##name(void)

SYSCALL(debug0);
SYSCALL(debug1);
SYSCALL(debug2);
SYSCALL(debug3);

extern long syscall_entry_64();
extern long syscall(long n, ...);

#endif