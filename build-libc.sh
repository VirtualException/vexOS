set -e

LIBNAME="vlibc"

CEXT="c"
ASMEXT="asm"

SRCDIR="vlibc/source/"
OUTDIR="vlibc/out/"


CFILES="${SRCDIR}*.${CEXT}"
ASMFILES="${SRCDIR}*.${ASMEXT}"

GCCARGS="-c -Ofast -Wall -Wextra -fno-stack-protector -fno-builtin -fno-stack-check -fshort-wchar -mno-red-zone -m64 -I vlibc/include/"
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