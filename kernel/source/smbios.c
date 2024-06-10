#include <vexos/bootinfo.h>
#include <vexos/printk.h>
#include <vexos/smbios.h>
#include <vexos/lib/memory.h>
#include <vexos/lib/def.h>

#define SMBIOS_MIN_ADDR 0xF0000
#define SMBIOS_MAX_ADDR 0xFFFFF
#define SMBIOS_STEP     0x10
#define SMBIOS_MAGIC    "_SM3_"

smbios_entry_t* smbios_entry = NULL;

void
smbios_setup() {

    printk(KERN_TLOG "Setting up SMBIOS... ");

    smbios_entry = (smbios_entry_t *) bootinfo.smbios_ptr;

    printk(KERN_LOG "smbios table struct max size: %d\n", smbios_entry->struct_max_size);
    printk(KERN_LOG "smbios table doc_rev: %u\n", smbios_entry->doc_rev);

    //volatile int i = *((int*) smbios_entry->table_addr);

    //smbios_get_table();

    printk(KERN_LOG "[DONE]\n");
}

void
smbios_get_table() {

    size_t struct_count = 0;

    uint64_t table_start = smbios_entry->table_addr; 
    size_t table_size  = smbios_entry->struct_max_size;

    uint64_t current_struct = table_start; 

    printk(KERN_LOG "Processing...\n");

    while (current_struct - table_start < table_size) {
        size_t current_table_size = smbios_table_len((smbios_header_t*) current_struct);
        current_struct += current_table_size;
        struct_count++;
    }

    printk(KERN_LOG "structs: %u\n", struct_count);

}

size_t
smbios_table_len(smbios_header_t *hd) {

    size_t i;
    volatile char *strtab = (char *)hd + hd->len;

    //printk(KERN_LOG "len: %d", hd->len);

    // double zero byte
    for (i = 1; strtab[i-1] != '\0' || strtab[i] != '\0'; i++)
        ;

    return hd->len + i + 1;
}

/*
void
smbios_setup_non_uefi()
{
    printk(KERN_TLOG "Setting up SMBIOS... ");

    char *mem = (char *) SMBIOS_MIN_ADDR;
    int length, i;
    uint8_t checksum = 0;

    while (mem < (char*) SMBIOS_MAX_ADDR + 1) {

        if (!memcmp(mem, SMBIOS_MAGIC, 5)) {

            printk(KERN_TLOG "%c\n", mem[0]);

            length = mem[5];
            checksum = 0;

            for (i = 0; i < length; i++)
                checksum += mem[i];

            if (checksum == 0)
                goto smbios_done;
        }

        mem += SMBIOS_STEP;
    }

    if ((uint64_t) mem == SMBIOS_MAX_ADDR + 1) {
        printk(KERN_LOG "[ERROR]\n");
        return;
    }

smbios_done:

    smbios_entry = (smbios_entry_t *) mem;

    printk(KERN_LOG "[DONE]\n");

    printk(KERN_TLOG  "smbios str (0x%X): %s\n", smbios_entry, smbios_entry->entry_string);

    return;
}
*/
