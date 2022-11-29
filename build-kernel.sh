set -e

KNAME="vexos64kernel"

CEXT="c"
ASMEXT="asm"

SRCDIR="kernel/source/"
OUTDIR="kernel/out/"

#LIBS="libc/out/libc.a"

CFILES="${SRCDIR}*.${CEXT}"
ASMFILES="${SRCDIR}*.${ASMEXT}"

GCCARGS="-c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include"
NASMARGS="-f elf64"
LDARGS="-nostdlib -static -T kernel/link/kernel.ld"

tput bold
echo "[Building '${KNAME}']"
tput sgr0

# Compile

echo "Compiling..."

for f in $CFILES; do
    gcc "$f" $GCCARGS -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
#gcc kernel/source/kernel.c -c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/kernel.o
#gcc kernel/source/keyboard.c -c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/keyboard.o
#gcc kernel/source/pcspkr.c -c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/pcspkr.o
#gcc kernel/source/ps2mouse.c -c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/ps2mouse.o
#gcc kernel/source/video.c -c -O2 -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/video.o
#gcc kernel/source/vtt.c -c -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I libc/include -o kernel/out/vtt.o
done

for f in $ASMFILES; do
    nasm "$f" $NASMARGS -o "${OUTDIR}$(basename ${f%.${ASMEXT}}.o)"
done

## Link

echo "Linking..."

OBJ="$(ls ${OUTDIR}*.o)"
LIBS="$(ls libc/out/*.o)"

ld $LDARGS $OBJ $LIBS -o "${OUTDIR}${KNAME}"

echo "Done!"
