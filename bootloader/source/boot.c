#define EXIT_BOOT_SERVICES 1
#define KERNELNAME L"vexos64kernel"

#define PREF_RES_X 1920
#define PREF_RES_Y 1080


#include <vexos_uefi/utils.h>
#include <vexos_uefi/efi_kinfo.h>


KernelEntry StartKernel;
KINFO*      KInfo;
CHAR16*     KernelPath = L"\\"KERNELNAME;
UINTN       MapKey;


EFI_STATUS PrintInfo() {

    Print(  WARNINGTXT
            " ██████╗ ███████╗██╗   ██╗██╗  ██╗         ██████╗ ██╗  ██╗    UEFI\n"
            "██╔═══██╗██╔════╝██║   ██║╚██╗██╔╝        ██╔════╝ ██║  ██║\n"
            "██║   ██║███████╗██║   ██║ ╚███╔╝         ███████╗ ███████║\n"
            "██║   ██║╚════██║╚██╗ ██╔╝ ██╔██╗         ██╔═══██╗╚════██║\n"
            "╚██████╔╝███████║ ╚████╔╝ ██╔╝ ██╗███████╗╚██████╔╝     ██║\n"
            " ╚═════╝ ╚══════╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝ ╚═════╝      ╚═╝\n\n\n");

    Print(  WARNINGTXT
            "PC Info:\n"
            "%N"
            "Architecture: %s\n"
            "Version: %s\n"
            "Kernel Path: [FSX:]%s\n"
            "%s\n\n",

        ARCHNAME, BUILDNUM, KernelPath, EXIT_BOOT_SERVICES ? L"(Will exit Boot Services)" : L"(Wont exit Boot Services)");

    Print(  WARNINGTXT
            "Graphics Output Protocol Info:\n"
            "%N"
            "Resolution: %dx%d\n"
            "Framebuffer addr: 0x%x\nFramebuffer size: %d\n\n",

        KInfo->VideoInfo.XRes, KInfo->VideoInfo.YRes, KInfo->VideoInfo.VMem, KInfo->VideoInfo.VMem_Size);

    PrintPause(WARNINGTXT L"\nPress any key to continue" NORMALTXT);

    ST->ConOut->ClearScreen(ST->ConOut);

    return EFI_SUCCESS;
}

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* ST) {

    InitializeLib(ImageHandle, ST);

    // Setup, video configuration and info dump

    Print(WARNINGTXT L"\n[ STARTING... ]\n" NORMALTXT);

    SetupEnv(&KInfo, PREF_RES_X, PREF_RES_Y);
    GetMemMapKey(&MapKey);
    PrintInfo();

    // Kernel loading and end of efi application

    StartKernel = SetupKernel(NULL, KernelPath, ImageHandle);

    if (StartKernel == NULL) {

        PrintPause(WARNINGTXT L"Press any key to restart" NORMALTXT);
        ST->RuntimeServices->ResetSystem(EfiResetWarm, EFI_ABORTED, 0, NULL);

    }

    PrintPause(WARNINGTXT L"[ BAILING OUT. GOOD LUCK! ]\n\nPress any key to continue" NORMALTXT);

    #if EXIT_BOOT_SERVICES
        ST->BootServices->ExitBootServices(ImageHandle, MapKey);
    #endif

    StartKernel(KInfo);

    return EFI_SUCCESS;
}