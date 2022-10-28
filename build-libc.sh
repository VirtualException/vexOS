set -e

LIBNAME="libc"

CEXT="c"
ASMEXT="asm"

SRCDIR="libc/source/"
OUTDIR="libc/out/"


CFILES="${SRCDIR}*.${CEXT}"
ASMFILES="${SRCDIR}*.${ASMEXT}"

GCCARGS="-c -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fshort-wchar -mno-red-zone -m64 -I libc/include/"
NASMARGS="-f elf64"

tput bold
echo "[Building C Library]"
tput sgr0

# Compile

echo "Compiling..."

for f in $CFILES; do
        gcc "$f" $GCCARGS -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
done

for f in $ASMFILES; do
        nasm "$f" $NASMARGS -o "${OUTDIR}$(basename ${f%.${ASMEXT}}.o)"
done

## Link

echo "Creating library..."

OBJS="$(ls ${OUTDIR}*.o)"

ar rs "${OUTDIR}${LIBNAME}.a" $OBJS

echo "Done!"