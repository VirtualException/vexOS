#include <vexos/kmem.h>
#include <vexos/printk.h>

#include <vexos/lib/memory.h>
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

size_t total_pages = 0;
size_t total_used_pages = 0;


typedef struct _kmem_block_t {

    uint64_t ptr;
    size_t size;

} kmem_block_t;

#define KMEM_USABLE_MAX 256

kmem_block_t usable_array[KMEM_USABLE_MAX] = { 0 };
size_t usable_count;

kmem_block_t *alloc_array;
size_t alloc_count;
size_t alloc_index;

uint64_t
kmem_setup() {

    total_pages = 0;
    usable_count = 0;

    printk(KERN_TLOG "Setting up memory...");

    uefi_memory_descriptor_t* desc = bootinfo.meminfo.map;
    uint64_t entries = bootinfo.meminfo.map_size / bootinfo.meminfo.desc_size;

    for (size_t i = 0; i < entries; i++) {

        size_t pages = desc->number_of_pages;

        total_pages += pages;

        if (desc->type == mem_type_conventional_memory) {

            if (usable_count > KMEM_USABLE_MAX - 1)
                printk(KERN_TLOG "Memory error: Entry cannot be saved. Reached maximum capacity of saving usable entries.\n");
            else
                usable_array[usable_count++] = (kmem_block_t) {
                    desc->physical_start, PAGES2B(pages)
                };
        }

        desc = NEXT_MEMORY_DESCRIPTOR(desc, bootinfo.meminfo.desc_size);

    }

    /* Find minimum entry to allocate "allocations" info into it */
    /* N pages = N*256 posible allocations */

    /* We start at i=1 becaouse i=0 is the entry where the kernel code is */
    size_t min_index = 0;
    for (size_t i = 1; i < usable_count; i++)
        if (usable_array[i].size < usable_array[min_index].size)
            min_index = i;

    alloc_index = 0;
    alloc_count = usable_array[min_index].size / sizeof (kmem_block_t);
    alloc_array = (kmem_block_t*) usable_array[min_index].ptr;

    /**
     * First allocation is done manually. It allocates the allocation table
     * itself, and occupies the whole memory entry. The rest of the entries are
     * saved after this entry, but the array is offsetted so that index 0 is
     * the first usable allocation entry.
    */
    alloc_array[0] = (kmem_block_t) { (uint64_t) alloc_array, usable_array[min_index].size };
    alloc_array++;

    printk(KERN_LOG "[DONE]\n");

    return 0;
}

void*
kmem_allocate_pages(size_t pages) {

    if (pages == 0)
        return NULL;

    uint64_t ptr = 0;

    /* Search for a free pages-long section in every usable memory entry */
    for (size_t e = 1; e < usable_count; e++) {

        /* Check if it fits in some part of the entry */

        ptr = usable_array[e].ptr;
        size_t a = 0;

        /**
         * Serach only in the e-th memory entry, while the allocation starting
         * from ptr fits in the usable memory entry 'e'.
        */
        while (ptr + pages * PAGE_SIZE < usable_array[e].ptr + usable_array[e].size) {

            bool collides = 0;

            /* Collides with any allocation? */
            for (size_t j = 0; j < alloc_count; j++) {

                /* If it does... */
                if ((ptr >= alloc_array[j].ptr && ptr < alloc_array[j].ptr + alloc_array[j].size) ||
                    (ptr <= alloc_array[j].ptr && ptr + pages * PAGE_SIZE >= alloc_array[j].ptr)) {
                    /* ...mark as colliding and try moving away by the-allocation-size bytes */
                    collides = 1;
                    ptr += alloc_array[a++].size;
                    break;
                }

            }

            /* If it does not collide, handle the success,... */
            if(!collides)
                goto allocate_success;

            /* ...otherwise, try again */

        }

    }

    /* No entry had enought space for the allocation */

    printk(KERN_TLOG "Memory error: Allocation failed: Memory section of %d pages not found.\n", pages);

    return NULL;

allocate_success: /* Yikes! */

    if (alloc_index >= alloc_count) {
        printk(KERN_TLOG "Memory error: Allocation failed: Run out of entries for allocations (%d/%d).\n",
            alloc_index, alloc_count);
        return NULL;
    }

    total_used_pages += pages;

    /* Save into the allocation entry the allocation just done. */
    alloc_array[alloc_index++] = (kmem_block_t) { ptr, pages * PAGE_SIZE };

    printk(KERN_TLOG "Memory: Allocated %d pages at 0x%08x. Using %d total pages.\n", pages, ptr, total_used_pages);

    return (void*) ptr;
}

void*
kmem_allocate(size_t bytes) {
    return kmem_allocate_pages((bytes + PAGE_SIZE - 1) / PAGE_SIZE);
}

void
kmem_deallocate(void *ptr) {

    uint64_t index;

    /* Find the index of the block to deallocate */
    for (index = 0; index < alloc_index; index++) {
        if (alloc_array[index].ptr == (uint64_t) ptr) {
            break;
        }
    }

    if (index == alloc_index) {
        printk(KERN_TLOG "Memory error: Invalid deallocation address.\n");
        return;
    }

    size_t pages = alloc_array[index].size / PAGE_SIZE;

    for (size_t i = index; i < alloc_index - 1; i++) {
        alloc_array[i] = alloc_array[i+1];
    }
    alloc_array[alloc_index - 1] = (kmem_block_t) { 0, 0 };
    alloc_index--;

    total_used_pages -= pages;

    printk(KERN_TLOG "Memory: Deallocated %d pages at 0x%08x. Using %d total pages\n", pages, ptr, total_used_pages);

    return;
}


void
kmem_print_info() {

/*
    uefi_memory_descriptor_t* desc = bootinfo.meminfo.map;
    uint64_t entries = bootinfo.meminfo.map_size / bootinfo.meminfo.desc_size;

    printk(KERN_TLOG "Memory Map Info: %d entries (showing conventional):\n", entries);

    for (size_t i = 0; i < entries; i++) {

        if (desc->type != mem_type_conventional_memory) {
            goto skip;
        }

        printk(KERN_TLOG "Entry %3d: %s  %8d KB  0x%010X to 0x%010X %c\n",
                i,
                uefi_memory_types_str[desc->type],
                BYTES2KiB(PAGES2B(desc->number_of_pages)),
                desc->physical_start,
                desc->physical_start + PAGES2B(desc->number_of_pages),
                (desc->type == mem_type_conventional_memory) ? '*' : ' '
            );

skip:
        desc = NEXT_MEMORY_DESCRIPTOR(desc, bootinfo.meminfo.desc_size);

    }
*/

    /* Usable memory review */

    for (size_t i = 0; i < usable_count; i++) {
        printk(KERN_TLOG "Usable entry %02d: %8d pages %8d KB  [ 0x%08X  0x%08X ]\n",
                i,
                usable_array[i].size / PAGE_SIZE,
                BYTES2KiB(usable_array[i].size),
                usable_array[i].ptr,
                usable_array[i].ptr + usable_array[i].size
            );
    }

    printk(KERN_TLOG "Total memory: %d Megabytes (%d pages)\n",
        BYTES2MiB(PAGES2B(total_pages)), total_pages);

    return;
}
