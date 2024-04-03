CC = gcc
LD = ld

NAME = BOOTX64.EFI

OUT = boot.so

SOURCE_DIR = source
HEADER_DIR = include
OUTPUT_DIR = out

SOURCES := $(shell find source/ -name '*.c')
OBJECTS := $(addprefix $(OUTPUT_DIR)/,$(SOURCES:source/%.c=%.o))

LIBS = -L /usr/lib/ -l:libgnuefi.a -l:libefi.a
EFI_CRT = /usr/lib/crt0-efi-x86_64.o

OPT_LEVEL = 3

CFLAGS = -Wall -Wextra -O3 -m64 \
		-fpic -fno-stack-protector -fno-builtin -fshort-wchar \
		-mno-red-zone -DEFI_FUNCTION_WRAPPER

LDFLAGS = -T /usr/lib/elf_x86_64_efi.lds -shared -Bsymbolic -nostdlib -znocombreloc -s

OBJCOPY = -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc \
		--target=efi-app-x86_64 --subsystem=10
# faltaria bootloader/out/boot.so bootloader/out/BOOTX64.EFI

# Compile bootloader
bootloader: $(OBJECTS)
	$(LD) $^ $(EFI_CRT) -o $(OUTPUT_DIR)/$(OUT) $(LDFLAGS) $(LIBS)
	objcopy $(OBJCOPY) $(OUTPUT_DIR)/$(OUT) $(OUTPUT_DIR)/$(NAME)

# Compile each .c file
$(OBJECTS): $(OUTPUT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $(CFLAGS) -O$(OPT_LEVEL) $< -o $@ -I $(HEADER_DIR)

# Remove binaries
clean:
	rm -f $(shell find -iname *.o)
	rm -f $(OUTPUT_DIR)/$(OUT)
	rm -f $(OUTPUT_DIR)/$(NAME)
