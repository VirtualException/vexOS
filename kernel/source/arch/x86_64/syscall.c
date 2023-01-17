#include <vexos/printk.h>
#include <vexos/arch/x86_64/io.h>
#include <vexos/arch/x86_64/syscall.h>
#include <vexos/lib/bool.h>

#define MSR_IA32_EFER       0xC0000080  /* Extended feature enables */
#define MSR_IA32_LSTAR      0xC0000082  /* Syscall target address */
#define MSR_IA32_EFER_SCE   0x00000001  /* Syscall enable bit*/

syscall_ptr syscall_table[NSYSCALLS] = { sys_debug0, sys_debug1, sys_debug2, sys_debug3 };

static bool done_setup = false;

uint64_t
syscall_setup() {

    if (done_setup) return (done_setup = 1);

    printk(KERN_LOG "Setting up syscalls...\n");

    /* Set syscall enable bit on */
    wrmsr(MSR_IA32_EFER, rdmsr(MSR_IA32_EFER) | MSR_IA32_EFER_SCE);

    /* Set syscall entry address */
    wrmsr(MSR_IA32_LSTAR, (uint64_t) syscall_entry_64);

    printk(KERN_LOG "Syscalls setup correctly\n");

    return 0;

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

long int
sys_debug3() {

    printk(KERN_LOG "SYSCALL 0x02\n");

    return 0;

}