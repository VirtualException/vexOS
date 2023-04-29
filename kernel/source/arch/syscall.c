#include <vexos/printk.h>
#include <vexos/memory.h>

#include <vexos/arch/io.h>
#include <vexos/arch/syscall.h>

#include <vexos/lib/bool.h>
#include <vexos/lib/assert.h>
#include <vexos/lib/macros.h>

#define MSR_IA32_EFER       0xC0000080  /* Extended feature enables */
#define MSR_IA32_STAR       0xC0000081  /* Syscall CS and SS */
#define MSR_IA32_LSTAR      0xC0000082  /* Syscall target address */
#define MSR_IA32_FMASK      0xC0000084  /* Flags mask */

#define MSR_IA32_EFER_SCE   0x00000001  /* Syscall enable bit*/


syscall_ptr syscall_table[SYSCALLS_N] = {
    x64_syscall_debug0,
    x64_syscall_debug1,
    x64_syscall_debug2,
    x64_syscall_debug3,
};

uint64_t
syscall_setup() {

    printk(KERN_LOG "Setting up syscalls...\n");

    /* Set syscall enable bit on */
    uint64_t old_msr =  rdmsr(MSR_IA32_EFER);
    wrmsr(MSR_IA32_EFER, old_msr | (uint64_t) MSR_IA32_EFER_SCE);

    /* "legacy" CS and SS stuff, no idea of what this is, but works */
    wrmsr(MSR_IA32_STAR, (uint64_t) 0x0008000800000000);

    /* Set syscall entry address */
    wrmsr(MSR_IA32_LSTAR, (uint64_t) syscall_entry_64);

    /* Dont clear any RFLAGS when entering a syscall */
    wrmsr(MSR_IA32_FMASK, (uint64_t) 0x0);

    printk(KERN_LOG "Testing syscalls:\n");
    syscall(0);

    printk(KERN_LOG "Syscalls set up correctly\n");

    return 0;

}

SYSCALL(debug0) {

    printk(KERN_LOG "SYSCALL 0x00\n");

    return 777;

}

SYSCALL(debug1) {

    printk(KERN_LOG "SYSCALL 0x01\n");

    return 0;

}

SYSCALL(debug2) {

    printk(KERN_LOG "SYSCALL 0x02\n");

    return 0;

}

SYSCALL(debug3) {

    printk(KERN_LOG "SYSCALL 0x02\n");

    return 0;

}