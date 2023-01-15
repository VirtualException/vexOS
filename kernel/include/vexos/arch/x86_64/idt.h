#ifndef _IDT_H
#define _IDT_H

#include <vlibc/stdint.h>
#include <vexos/utils/macros.h>

#define IDT_PAGE_FAULT          0xE


#define IDT_TA_INTERRUPTGATE    0b10001110
#define IDT_TA_CALLGATE         0b10001100
#define IDT_TA_TRAPGATE         0b10001111

#define IDT_DESCRIPTORS 256

typedef
void (__sysv_abi *interrupt) (
    void*  time
);

typedef struct __packed {

    uint16_t size;
    uint64_t ptr;

} idt_ptr;

typedef struct __packed {

    /* 16 bytes */

    uint16_t    offset_0;   // offset bits 0..15
    uint16_t    selector;   // a code segment selector in GDT or LDT
    uint8_t     ist;        // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t     type_attr;  // gate type, dpl, and p fields
    uint16_t    offset_1;   // offset bits 16..31
    uint32_t    offset_2;   // offset bits 32..63
    uint32_t    reserved;   // reserved

} idt_desc;

uint64_t    idt_setup(void);
extern void idt_load(idt_ptr* idt);
void        idt_create_desc(idt_desc* idt, uint64_t index, uint64_t type, uint64_t selector, uint64_t offset);
void        idt_set_offset(idt_desc* idt, uint64_t offset);
uint64_t    idt_get_offset(idt_desc* idt);

struct interrupt_frame;

__interrupt
void
int_handler(struct interrupt_frame* intframe);


#endif