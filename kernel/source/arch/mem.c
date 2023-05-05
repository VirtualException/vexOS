#include <vexos/arch/mem.h>
#include <vexos/printk.h>
#include <vexos/lib/bool.h>
#include <vexos/lib/def.h>


char uefi_memory_types_str[14][256] = {

    "reserved_memory",
    "uefi_loader_code",
    "uefi_loader_data",
    "boot_services_code",
    "boot_services_data",
    "runtime_services_code",
    "runtime_services_data",
    "conventional_memory",
    "unusable_memory",
    "acpi_reclaim_memory",
    "acpi_memory_nvs",
    "memory_mapped_io",
    "memory_mapped_io_port",
    "firmware_pal_code",

};

uint64_t mem_total_bytes = 0;
uint64_t mem_total_pages = 0;

uint64_t usable_mem_arr[32] = { 0 };
uint64_t usable_mem_arr_size = 0;

static bool done_setup = false;

uint64_t mem_setup(void) {

    if (done_setup) return done_setup = true;

    mem_total_bytes = 0;
    mem_total_pages = 0;
    usable_mem_arr_size = 0;

    printk(KERN_TLOG "Checking memory layout...\n");

    uefi_memory_descriptor* desc = kinfo->meminfo.map;
    uint64_t entries = kinfo->meminfo.map_size /kinfo->meminfo.desc_size;

    for (size_t i = 0; i < entries; i++) {

        mem_total_pages += desc->number_of_pages;
        mem_total_bytes += PAGES2B(desc->number_of_pages);

        if (desc->type == mem_type_conventional_memory) {
            usable_mem_arr[usable_mem_arr_size++] = i;
        }

        desc = NEXT_MEMORY_DESCRIPTOR(desc, kinfo->meminfo.desc_size);

    }

    printk(KERN_TLOG "Total memory: %d Megabytes (%d pages)\n", BYTES2MB(mem_total_bytes), mem_total_pages);

    return 0;
}

void* mem_allocate(size_t bytes) {

    for (size_t i = 0; i < usable_mem_arr_size; i++) {

        uefi_memory_descriptor* desc = NEXT_MEMORY_DESCRIPTOR(kinfo->meminfo.map, kinfo->meminfo.desc_size * usable_mem_arr[i]);

        if (PAGES2B(desc->number_of_pages) >= bytes) {
            return (void*) desc->physical_start;
        }

    }

    return NULL;

}