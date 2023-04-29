#ifndef _DT_H
#define _DT_H

#include <vexos/lib/types.h>
#include <vexos/lib/macros.h>

#define GDT_DESCRIPTORS 4

#define IDT_TA_INTERRUPTGATE    0b10001110
#define IDT_TA_CALLGATE         0b10001100
#define IDT_TA_TRAPGATE         0b10001111

#define IDTENTRY(offset, type, selector) (idt_entry){ \
                                                    (((uint64_t)offset) & 0x000000000000ffff), selector, 0, type, \
                                                    (((uint64_t)offset) & 0x00000000ffff0000) >> 16, \
                                                    (((uint64_t)offset) & 0xffffffff00000000) >> 32, \
                                                    0 \
                                                    }


typedef struct __packed {

    uint16_t size;
    uint64_t ptr;

} gdt_desc, idt_desc;

typedef struct __packed {

    uint16_t    limit_0;
    uint16_t    base_0;
    uint8_t     base_1;
    uint8_t     access_byte;
    uint8_t     limit_1_flags;
    uint8_t     base_2;

} gdt_entry;

typedef struct __packed {

    /* 16 bytes */

    uint16_t    offset_0;   // offset bits 0..15
    uint16_t    selector;   // a code segment selector in GDT or LDT
    uint8_t     ist;        // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t     type_attr;  // gate type, dpl, and p fields
    uint16_t    offset_1;   // offset bits 16..31
    uint32_t    offset_2;   // offset bits 32..63
    uint32_t    reserved;   // reserved

} idt_entry;

uint64_t    gdt_setup(void);
extern void gdt_load(gdt_desc* gdt);

uint64_t    idt_setup(void);
extern void idt_load(idt_desc* idt);

#endif