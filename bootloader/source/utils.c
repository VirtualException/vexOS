#include <vexos_uefi/utils.h>

#define _FONTDATA
#include "../../vga8x16.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL*   gop;
EFI_RNG_PROTOCOL*               rng;

EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GUID rngGuid = EFI_RNG_PROTOCOL_GUID;

EFI_FILE*   Kernel;
Elf64_Ehdr  KernelHeader;

KernelEntry
SetupKernel(EFI_FILE* Directory, CHAR16* KernelPath, EFI_HANDLE ImageHandle) {

    EFI_LOADED_IMAGE_PROTOCOL*          LoadedImage = NULL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*    FileSystem  = NULL;

    UINTN           FileInfoSize;
    EFI_FILE_INFO*  FileInfo;

    Elf64_Phdr* phdrs;

    Print(WARNINGTXT);

    ST->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    ST->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

    if (Directory == NULL) {
        FileSystem->OpenVolume(FileSystem, &Directory);
    }

    Print(L"[ OPENING VEXOS-KERNEL FROM: %s ]\n", KernelPath);

    if (Directory->Open(Directory, &Kernel, KernelPath, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY)) {
        Print(L"[ ERROR WHILE OPENING DIRECTORY ]\n");
        return NULL;
    }

    if (Kernel==NULL) {
        Print(L"[ ERROR OPENING VEXOS-KERNEL ]\n");
        return NULL;
    }
    else Print(L"[ LOADING VEXOS-KERNEL ]\n");

    // Create entry point of the kernel

    Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
    ST->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
    Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);

    UINTN size = sizeof(KernelHeader);
    Kernel->Read(Kernel, &size, &KernelHeader);

    // Check for bad format

    if (CompareMem(&KernelHeader.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0  ||
                KernelHeader.e_ident[EI_CLASS]    != ELFCLASS64       ||
                KernelHeader.e_ident[EI_DATA]     != ELFDATA2LSB      ||
                KernelHeader.e_type               != ET_EXEC          ||
                KernelHeader.e_machine            != EM_X86_64        ||
                KernelHeader.e_version            != EV_CURRENT ) {
        Print(L"[ VEXOS-KERNEL FORMAT IS UNSUPPORTED OR CORRUPTED ]\n");
        return NULL;
    }
    else {
        Print(L"[ VEXOS-KERNEL HEADER SUCCESSFULLY VERIFIED ] : (Executable file, elf-x64_64, Little Endian)\n");
    }

    // Allocate kernel entry memory

    Kernel->SetPosition(Kernel, KernelHeader.e_phoff);
    size = KernelHeader.e_phnum * KernelHeader.e_phentsize;
    ST->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
    Kernel->Read(Kernel, &size, phdrs);

    // Find entry point

    Print(L"[ FINDING ENTRY POINT ]\n");

    for (Elf64_Phdr* phdr = phdrs;
        (char*)phdr < (char*)phdrs + KernelHeader.e_phnum * KernelHeader.e_phentsize;
        phdr = (Elf64_Phdr*)((char*)phdr + KernelHeader.e_phentsize)) {

        switch (phdr->p_type) {

            case PT_LOAD:
            Elf64_Xword pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
            Elf64_Addr segment = phdr->p_paddr;
            ST->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

            Kernel->SetPosition(Kernel, phdr->p_offset);
            UINTN size = phdr->p_filesz;
            Kernel->Read(Kernel, &size, (void*)segment);

            Kernel->Close(Kernel);

            return (KernelEntry) KernelHeader.e_entry;
        }
    }

    Print(L"[ COULDN'T FIND ENTRY POINT ]\n");

    return NULL;

}

EFI_STATUS
GetMemMapKey(UINTN* MapKey) {

    EFI_MEMORY_DESCRIPTOR* MemMap = NULL;
    EFI_STATUS Status   = EFI_SUCCESS;

    UINT32  Ver         = 0;
    UINTN   DescSize    = 0;
    UINTN   MemMapSize  = 0;

    Status = BS->GetMemoryMap(&MemMapSize, MemMap, MapKey, &DescSize, &Ver);

    if (Status == EFI_BUFFER_TOO_SMALL) {

        UINTN encompassing_size = MemMapSize + (2 * DescSize);
        void *buffer = NULL;

        Status = BS->AllocatePool(EfiLoaderData, encompassing_size, &buffer);

        MemMap      = (EFI_MEMORY_DESCRIPTOR*) buffer;
        MemMapSize  = encompassing_size;
        Status      = BS->GetMemoryMap(&MemMapSize, MemMap, MapKey, &DescSize, &Ver);

    }
    else if (Status == EFI_SUCCESS) {
        Print(L"GetMemoryMap error\n");
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

    (*KInfo)->BackBuffer    = AllocateZeroPool(gop->Mode->FrameBufferSize);

    (*KInfo)->VideoInfo     = (VIDEO_INFO) {
                                gopInfo->HorizontalResolution,
                                gopInfo->VerticalResolution,
                                gop->Mode->FrameBufferBase,
                                gop->Mode->FrameBufferSize,
                            };

    (*KInfo)->Reset         = RT->ResetSystem;

    (*KInfo)->GetTime       = ST->RuntimeServices->GetTime;

    (*KInfo)->Font          = (FONT) {
                                FONT_BMP_WDTH, FONT_BMP_HGHT, FONT_WDTH, FONT_HGHT, FONT_BPP,
                                AllocateZeroPool(FONT_SIZE),
                            };

    CopyMem((*KInfo)->Font.Bmp, font_data, FONT_SIZE);

    //(*KInfo)->Font.Bmp = (PIXEL*) font_data;

    return EFI_SUCCESS;
}