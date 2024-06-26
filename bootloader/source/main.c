#define KERNELNAME L"vexos64kernel"
#define EXIT_BOOT_SERVICES 1

#define PREF_RES_X 1920
#define PREF_RES_Y 1080

#include <vexos_uefi/utils.h>

KernelEntry     start_kernel;
KERNEL_INFO*    KInfo;
CHAR16*         KernelPath = L"\\"KERNELNAME;
UINTN           MapKey;

EFI_STATUS PrintInfo() {

    Print(  WARNINGTXT
            L" ____   ____   ____ _______                   ____   _____\n"
            L"|  _ \\ / __ \\ / __ \\__   __|                 / __ \\ / ____|\n"
            L"| |_) | |  | | |  | | | |    __   _______  _| |  | | (___\n"
            L"|  _ <| |  | | |  | | | |    \\ \\ / / _ \\ \\/ / |  | |\\___ \\\n"
            L"| |_) | |__| | |__| | | |     \\ V /  __/>  <| |__| |____) |\n"
            L"|____/ \\____/ \\____/  |_|      \\_/ \\___/_/\\_\\\\____/|_____/\n\n\n"
            NORMALTXT
        );

    Print(  WARNINGTXT
            L"PC Info:\n"
            L"%N"
            L"Architecture: %s\n"
            L"Build: %s\n"
            L"Kernel Path: [FSX:]%s\n"
            L"Memory Map: %s\n"
            L"%s\n\n"
            NORMALTXT,

            ARCHNAME, BUILDNUM, KernelPath,
            KInfo->MemInfo.Map ? L"Ok" : L"Bad",
            EXIT_BOOT_SERVICES ? L"(Will exit Boot Services)" : L"(Wont exit Boot Services)"
        );

    Print(  WARNINGTXT
            L"Graphics Output Protocol Info:\n"
            L"%N"
            L"Resolution: %dx%d\n"
            L"Framebuffer addr: 0x%x\nFramebuffer size: %d\n\n"
            NORMALTXT,

            KInfo->VideoInfo.XRes, KInfo->VideoInfo.YRes, KInfo->VideoInfo.VMem, KInfo->VideoInfo.VMem_Size
        );

    PrintPause(WARNINGTXT L"\nPress any key to continue" NORMALTXT);

    ST->ConOut->ClearScreen(ST->ConOut);

    return EFI_SUCCESS;
}

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* ST) {

    InitializeLib(ImageHandle, ST);

    /* Setup, video configuration and info dump */

    Print(WARNINGTXT L"\n[ STARTING... ]\n" NORMALTXT);

    SetupMemMap(&MapKey);
    SetupEnv(&KInfo, PREF_RES_X, PREF_RES_Y);
    PrintInfo();

    /* Kernel loading and end of efi application */

    start_kernel = SetupKernel(KernelPath, ImageHandle);

    if (start_kernel == NULL) {

        PrintPause(WARNINGTXT L"An error ocurred. Press any key to restart" NORMALTXT);

        ST->RuntimeServices->ResetSystem(EfiResetWarm, EFI_ABORTED, 0, NULL);

    }

    Print(WARNINGTXT L"[ BAILING OUT. GOOD LUCK! ]\n" NORMALTXT);
    PrintPause(WARNINGTXT "\nPress any key to continue\n\r\n\r" NORMALTXT);

#if EXIT_BOOT_SERVICES
    ST->BootServices->ExitBootServices(ImageHandle, MapKey);
#endif

    start_kernel(KInfo);

    return EFI_SUCCESS;
}
