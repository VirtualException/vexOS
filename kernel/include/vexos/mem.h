#ifndef _MEM_H
#define _MEM_H

#include <vexos/lib/types.h>
#include <vexos/bootinfo.h>

/* from gnu-efi */
#define NEXT_MEMORY_DESCRIPTOR(ptr, size) ((uefi_memory_descriptor_t*) (((uint8_t*) ptr) + size))

#define PAGE_SIZE   4096
#define PAGES2B(p)  ((p) * PAGE_SIZE)

#define BYTES2KB(b) ((b) / 1024)
#define BYTES2MB(b) ((b) / 1048576)

extern char uefi_memory_types_str[14][256];

enum uefi_memory_types {

    mem_type_reserved_memory,
    mem_type_loader_code,
    mem_type_loader_data,
    mem_type_boot_services_code,
    mem_type_boot_services_data,
    mem_type_runtime_services_code,
    mem_type_runtime_services_data,
    mem_type_conventional_memory,
    mem_type_unusable_memory,
    mem_type_acpi_reclaim_memory,
    mem_type_acpi_memory_nvs,
    mem_type_memory_mapped_io,
    mem_type_memory_mapped_io_port_space,
    mem_type_pal_code,

};

uint64_t mem_setup();
void mem_review();

void* mem_allocate(size_t bytes);

#endif
