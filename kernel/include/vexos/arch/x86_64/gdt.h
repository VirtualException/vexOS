#ifndef _GDT_H
#define _GDT_H

#include <vexos/lib/types.h>
#include <vexos/lib/macros.h>

#define SEG_DESCTYPE(x)     ((x) << 0x04)           // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)         ((x) << 0x07)           // Present
#define SEG_SAVL(x)         ((x) << 0x0C)           // Available for system use
#define SEG_LONG(x)         ((x) << 0x0D)           // Long mode
#define SEG_SIZE(x)         ((x) << 0x0E)           // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)         ((x) << 0x0F)           // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)         (((x) &  0x03) << 0x05) // Set privilege level (0 - 3)

#define SEG_DATA_RD         0x00 // Read-Only
#define SEG_DATA_RDA        0x01 // Read-Only, accessed
#define SEG_DATA_RDWR       0x02 // Read/Write
#define SEG_DATA_RDWRA      0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD     0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA    0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD   0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA  0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX         0x08 // Execute-Only
#define SEG_CODE_EXA        0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD       0x0A // Execute/Read
#define SEG_CODE_EXRDA      0x0B // Execute/Read, accessed
#define SEG_CODE_EXC        0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA       0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC      0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA     0x0F // Execute/Read, conforming, accessed

#define GDT_DESCRIPTORS 4

typedef struct __packed {

    uint16_t size;
    uint64_t ptr;

} gdt_ptr;

typedef struct __packed {

    uint16_t    limit_0;
    uint16_t    base_0;
    uint8_t     base_1;
    uint8_t     access_byte;
    uint8_t     limit_1_flags;
    uint8_t     base_2;

} gdt_desc;

uint64_t    gdt_setup(void);
extern void gdt_load(gdt_ptr* gdt);

#endif