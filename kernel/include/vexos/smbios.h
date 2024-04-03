#ifndef _SMBIOS_H
#define _SMBIOS_H

#include <vexos/lib/attributes.h>
#include <vexos/lib/types.h>

typedef struct smbios_entry_t {

    int8_t      entry_string[4];    // This is _SM3_
    uint8_t     checksum;           // 0 (overflow) when added with the rest of the bytes
    uint8_t     length;             // Length of the Entry Point Table
    uint8_t     major_ver;          // Major Version
    uint8_t     minor_ver;          // Minor Version
    uint8_t     doc_rev;            // Docrev
    uint8_t     entry_rev;          // Entry Revision
    uint8_t     reserved;           // Reserved
    uint32_t    struct_max_size;    // Maximum size of the smbios table struct
    uint64_t    table_addr;         // Address of the Table

} __packed smbios_entry_t;


typedef struct smbios_header_t {

    uint8_t type;
    uint8_t len;
    uint16_t handle;

} __packed smbios_header_t;

void smbios_setup();
void smbios_get_table();
size_t smbios_table_len(smbios_header_t *hd);

#endif
