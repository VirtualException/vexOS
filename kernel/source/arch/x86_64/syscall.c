#include <vexos/printk.h>
#include <vexos/arch/x86_64/syscall.h>
#include <vexos/utils/macros.h>

syscall_ptr syscall_table[NSYSCALLS] = { 0 };

void
syscall_setup() {

    printk(KERN_LOG "Setting up syscalls...\n");

    syscall_table[0] = sys_debug0;
    syscall_table[1] = sys_debug1;
    syscall_table[2] = sys_debug2;

    syscall_enable(((uint64_t)syscall_entry_64) & 0x00000000ffffffff, (((uint64_t)syscall_entry_64) & 0xffffffff00000000) >> 32);

    printk(KERN_LOG "Syscalls setup correctly\n");

}

long int
sys_debug0() {

    printk(KERN_LOG "SYSCALL 0x00\n");

    return 0;

}

long int
sys_debug1() {

    printk(KERN_LOG "SYSCALL 0x01\n");

    return 0;

}

long int
sys_debug2() {

    printk(KERN_LOG "SYSCALL 0x02\n");

    return 0;

}