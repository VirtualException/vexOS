#include <vexos_uefi/utils.h>

#define _FONTDATA
#include "../../font/font.h"

char magic_val[8] = MAGIC_VAL;


EFI_GRAPHICS_OUTPUT_PROTOCOL*   gop;

EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GUID lipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;

EFI_MEMORY_DESCRIPTOR* MemMap;
UINT32  MemDescVersion;
UINTN   MemDescSize;
UINTN   MemMapSize;

/*

Easy way:

    UINT64 Addr = <base_address>; // 0x0
    UINT64 Size = LibFileInfo(KernelFile)->FileSize;
    ST->BootServices->AllocatePages(AllocateAddress, EfiConventionalMemory, 16, &Addr);
    KernelFile->SetPosition(KernelFile, <offset_to_code>); // 0x1000
    KernelFile->Read(KernelFile, &Size, (void*) Addr);

    return <entry_point>;

*/

KernelEntry
SetupKernel(CHAR16* KernelPath, EFI_HANDLE ImageHandle) {

    /* Opening the file */

    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_FILE_HANDLE Volume;
    EFI_FILE_HANDLE KernelFile;

    BS->HandleProtocol(ImageHandle, &lipGuid, (void **) &LoadedImage);
    Volume = LibOpenRoot(LoadedImage->DeviceHandle);

    Volume->Open(Volume, &KernelFile, KernelPath,
        EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);

    Print(WARNINGTXT);

    if (KernelFile == NULL) {
        Print(L"[ COULD NOT OPEN VEXOS KERNEL FROM \"%s\" ]\n", KernelPath);
        return NULL;
    }
    Print(L"[ VEXOS KERNEL FILE OPENED FROM \"%s\" ]\n", KernelPath);

    /* Reading from the ELF kernel file */

    Elf64_Ehdr KernelHdr;
    UINT64 HdrSize = sizeof (KernelHdr);

    KernelFile->SetPosition(KernelFile, 0);
    KernelFile->Read(KernelFile, &HdrSize, &KernelHdr);

    if ( CompareMem(KernelHdr.e_ident, ELFMAG, SELFMAG)         ||
                    KernelHdr.e_ident[EI_CLASS]  != ELFCLASS64  ||
                    KernelHdr.e_ident[EI_DATA]   != ELFDATA2LSB ||
                    KernelHdr.e_type             != ET_EXEC     ||
                    KernelHdr.e_machine          != EM_X86_64   ||
                    KernelHdr.e_version          != EV_CURRENT ) {

        Print(L"[ VEXOS KERNEL FORMAT UNSUPPORTED ]\n");
        return NULL;
    }
    Print(L"[ VEXOS KERNEL *ELF* FORMAT SUCCESFULLY VERIFIED ]\n");

    /* Find the loadable segment and get the entry point */

    Elf64_Phdr* KernelPhdr;
    UINT64 PhdrSize = KernelHdr.e_phnum * KernelHdr.e_phentsize;

    ST->BootServices->AllocatePool(EfiLoaderData, PhdrSize, (void**)&KernelPhdr);
    KernelFile->SetPosition(KernelFile, KernelHdr.e_phoff);
    KernelFile->Read(KernelFile, &PhdrSize, (void*)KernelPhdr);

    Print(L"[ LOADING VEXOS KERNEL ]\n");

    for (Elf64_Phdr* Phdr = KernelPhdr;
        (uint64_t) Phdr < (uint64_t) KernelPhdr + PhdrSize;
        Phdr = (Elf64_Phdr*) (uint64_t) Phdr + KernelHdr.e_phentsize) {

        switch (Phdr->p_type) {

        case PT_LOAD:

            Print(L"[ LOADABLE SEGMENT FOUND ]\n");

            UINT64 Pages    = Phdr->p_memsz / PAGE_SIZE;
            UINT64 FileSize = Phdr->p_filesz;
            UINT64 SegAddr  = Phdr->p_paddr;

            ST->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, Pages, &SegAddr);

            KernelFile->SetPosition(KernelFile, Phdr->p_offset);
            KernelFile->Read(KernelFile, &FileSize, (void*) SegAddr);

            KernelFile->Close(KernelFile);

            Print(L"[ DONE. RETURNING ENTRY POINT: 0x%X ]\n", KernelHdr.e_entry);

            return (KernelEntry) KernelHdr.e_entry;

        default:

            Print(L"[ UNSUPPORTED SEGMENT FOUND ]\n");

            /* Unsupported segment */

            break;

        }
    }

    return NULL;

}

EFI_STATUS
SetupMemMap(UINTN* MapKey) {

    EFI_STATUS Status = EFI_SUCCESS;

    Status = BS->GetMemoryMap(&MemMapSize, MemMap, MapKey, &MemDescSize, &MemDescVersion);

    if (Status == EFI_BUFFER_TOO_SMALL) {

        UINTN NewSize   = MemMapSize + (2 * MemDescSize);
        VOID* Buffer    = NULL;

        Status = BS->AllocatePool(EfiLoaderData, NewSize, &Buffer);

        MemMap      = (EFI_MEMORY_DESCRIPTOR*) Buffer;
        MemMapSize  = NewSize;

        Status = BS->GetMemoryMap(&MemMapSize, MemMap, MapKey, &MemDescSize, &MemDescVersion);

    }
    else {
        Print(WARNINGTXT L"[ GetMemoryMap ERROR ]\n" NORMALTXT);
    }

    return Status;
}

EFI_STATUS
SetupEnv(KERNEL_INFO** KInfo, UINT32 PrefResX, UINT32 PrefResY) {

    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* gopInfo;
    UINTN InfoSize, MaxMode;

    ST->BootServices->LocateProtocol(&gopGuid, NULL, (void**)&gop);

    gop->QueryMode(gop, 0, &InfoSize, &gopInfo);

    MaxMode = gop->Mode->MaxMode;

    if (PrefResX == 0 || PrefResY == 0) {
        gop->SetMode(gop, gop->Mode->Mode);
        goto skip_video_setup;
    }

    for (UINT32 i = 0; i < MaxMode; gop->QueryMode(gop, i++, &InfoSize, &gopInfo)) {

        if (gopInfo->HorizontalResolution   == (UINT32) PrefResX &&
            gopInfo->VerticalResolution     == (UINT32) PrefResY) {

            gop->SetMode(gop, i);
            ST->ConOut->ClearScreen(ST->ConOut);
            break;
        }
    }

skip_video_setup:

    *KInfo                  = AllocateZeroPool(sizeof(VIDEO_INFO));

    (*KInfo)->Magic         = *(uint64_t*)magic_val;

    (*KInfo)->BackBuffer    = AllocateZeroPool(gop->Mode->FrameBufferSize);

    (*KInfo)->VideoInfo     = (VIDEO_INFO) {
                                gop->Mode->Info->HorizontalResolution, //gopInfo->HorizontalResolution,
                                gopInfo->VerticalResolution,
                                gop->Mode->FrameBufferBase,
                                gop->Mode->FrameBufferSize,
                            };

    (*KInfo)->MemInfo       = (MEMORY_INFO) {
                                MemMap,
                                MemMapSize,
                                MemDescSize,
                                MemDescVersion,
                            };

    (*KInfo)->Reset         = RT->ResetSystem;

    (*KInfo)->GetTime       = ST->RuntimeServices->GetTime;

    (*KInfo)->Font          = (FONT) {
                                FONT_CHARS, CHAR_WDTH, CHAR_HGHT, FONT_BPP,
                                AllocateZeroPool(FONT_SIZE),
                            };

    CopyMem((*KInfo)->Font.Bmp, font_data, FONT_SIZE);

    return EFI_SUCCESS;
}
