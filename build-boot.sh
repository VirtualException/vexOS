set -e

tput bold
echo "[Building bootloader]"
tput sgr0

# Compile

echo "Compiling..."

gcc     bootloader/source/boot.c \
        -Ofast -c -Wall -Wextra -m64 -fpic -fno-stack-protector -fno-builtin -fshort-wchar -mno-red-zone \
        -DEFI_FUNCTION_WRAPPER \
        -I bootloader/include \
        -o bootloader/out/boot.o

gcc     bootloader/source/utils.c \
        -Ofast -c -Wall -Wextra -m64 -fpic -fno-stack-protector -fno-builtin -fshort-wchar -mno-red-zone \
        -I bootloader/include \
        -o bootloader/out/utils.o

# Link

echo "Linking..."

ld      bootloader/out/boot.o bootloader/out/utils.o /usr/lib/crt0-efi-x86_64.o \
        -T /usr/lib/elf_x86_64_efi.lds \
        -shared -Bsymbolic -nostdlib -znocombreloc \
        -L /usr/lib/ -l:libgnuefi.a -l:libefi.a \
        -o bootloader/out/boot.so

# Copy

objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc \
        --target=efi-app-x86_64 --subsystem=10 \
        bootloader/out/boot.so bootloader/out/BOOTX64.EFI

echo "Done!"