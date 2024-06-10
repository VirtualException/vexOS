CC = gcc
ASM = nasm
LD = ld

NAME = vexos64kernel

SOURCE_DIR = source
HEADER_DIR = include
OUTPUT_DIR = out

SOURCES_C := $(shell find source/ -name '*.c')
SOURCES_ASM := $(shell find source/ -name '*.asm')

HEADERS := $(shell find include/ -name '*.h')

# Files to exclude from being optimized
SOURCES_NO_OPT = source/printk.c

OBJECTS_C := $(addprefix $(OUTPUT_DIR)/,$(SOURCES_C:source/%.c=%.o))
OBJECTS_C_NO_OPT := $(addprefix $(OUTPUT_DIR)/,$(SOURCES_NO_OPT:source/%.c=%.o))
OBJECTS_ASM := $(addprefix $(OUTPUT_DIR)/,$(SOURCES_ASM:source/%.asm=%.o))

LIBS =

DEBUG = 0
OPT_LEVEL = 3

CFLAGS = -Wall -Wextra -nostdlib -fmacro-prefix-map="kernel/source/"="" \
		-m64 -mtune=native -mcmodel=large -mno-red-zone -mlarge-data-threshold=64 \
		-mfpmath=sse \
		-mmmx -msse -msse2 -msse3 -mssse3 -msse4 -m3dnow \
		-fno-stack-protector -fno-stack-check -fno-builtin \
		-ffreestanding -fpic -fpie

NASMFLAGS = -f elf64

LDFLAGS = -nostdlib -static -T link/kernel.ld -no-warn-rwx-segments -z max-page-size=0x1000

# Compile kernel
kernel: $(OBJECTS_C) $(OBJECTS_ASM)
	$(LD) -o $(OUTPUT_DIR)/$(NAME) $^ $(LDFLAGS)

# Compile kernel with debug flags
debug: CFLAGS += -g -D__DEBUG__
debug: OPT_LEVEL = g
debug: SOURCES_NO_OPT =
debug: clean kernel

$(OBJECTS_C_NO_OPT): OPT_LEVEL = 0

# Compile each .c file
$(OBJECTS_C): $(OUTPUT_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	$(CC) -c $(CFLAGS) -O$(OPT_LEVEL) $< -o $@ -I $(HEADER_DIR)

# Compile each .asm file
$(OBJECTS_ASM): $(OUTPUT_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(ASM) $(NASMFLAGS) $< -o $@

# Remove binaries
clean:
	rm -f $(shell find -iname *.o)
	rm -f $(OUTPUT_DIR)/$(NAME)
