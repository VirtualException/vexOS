#include <libc/stdint.h>
#include <vexos/dt.h>

#define ASM(x) asm volatile(x)


int
gdt_setup(void) {

    ASM("cli");

    dt_ptr      gdt;
    gdt_desc    desc_table[GDT_DESCRIPTORS];

    gdt.ptr     = (uint64_t) desc_table;
    gdt.size    = sizeof(gdt_desc) * GDT_DESCRIPTORS;

    gdt_create_entry(&desc_table[0], 0, 0, 0, 0);                             /* Null Descriptor */
    gdt_create_entry(&desc_table[1], 0x00400000, 0x003FFFFF, 0x0C, 0x9A);     /* Kernel Mode Code Segment */
    gdt_create_entry(&desc_table[2], 0x00800000, 0x003FFFFF, 0x0C, 0x92);     /* Kernel Mode Data Segment */
    gdt_create_entry(&desc_table[3], 0, 0, 0, 0);
    /*gdt_create_entry(&ents[3], &TSS, sizeof(TSS), 0x00, 0x89);*/      /* Task State*/

    gdt_load(&gdt);

    asm volatile("sti");

    return 0;
}

int
gdt_create_entry(gdt_desc* ent, uint64_t limit, uint64_t base, uint64_t flags, uint64_t access_byte) {

    // Check the limit to make sure that it can be encoded
    if (limit > 0xFFFFF) return -1;

    // Encode the limit
    ent->data[0] = limit & 0xFF;
    ent->data[1] = (limit >> 8) & 0xFF;
    ent->data[6] = (limit >> 16) & 0x0F;

    // Encode the base
    ent->data[2] = base & 0xFF;
    ent->data[3] = (base >> 8) & 0xFF;
    ent->data[7] = (base >> 24) & 0xFF;
    ent->data[4] = (base >> 16) & 0xFF;

    // Encode the access byte
    ent->data[5] = access_byte;

    // Encode the flags
    ent->data[6] |= (flags << 4);

    return 0;
}

int idt_setup(void) {

    asm volatile("cli");

    dt_ptr      idt;
    idt_desc    int_table[IDT_DESCRIPTORS];

    idt.ptr     = (uint64_t) int_table;
    idt.size    = sizeof(idt_desc) * IDT_DESCRIPTORS;

    int_table[0].offset_1 = 0;
    int_table[0].offset_2 = 0;
    int_table[0].offset_3 = 0;
    int_table[0].selector = 0;
    int_table[0].ist = 0;
    int_table[0].zero = 0;

    idt_load(&idt);

    asm volatile("sti");

    return 0;
}


void readmsr(unsigned int msr, unsigned int *lo, unsigned int *hi) {

   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));

}