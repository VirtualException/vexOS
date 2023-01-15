set -e

KNAME="vexos64kernel"

CEXT="c"
ASMEXT="asm"

EXCLUDE_OPT="printk.c"

SRCDIR="kernel/source/"
OUTDIR="kernel/out/"

LIBS="vlibc/out/vlibc.a"

CFILES="$(find ${SRCDIR} -name \*.${CEXT})"
ASMFILES="$(find ${SRCDIR} -name \*.${ASMEXT})"

GCCARGS="-c -O3 -mgeneral-regs-only -Wall -Wextra -fno-stack-protector -fno-stack-check -fno-builtin -fno-pic -fPIE -fshort-wchar -mno-red-zone -m64 -I kernel/include -I vlibc/include/"
NASMARGS="-f elf64"
LDARGS="-nostdlib -static -T kernel/link/kernel.ld"

tput bold
echo "[Building '${KNAME}']"
tput sgr0

# Compile

echo "Compiling..."

for f in $CFILES; do
    if [ "$EXCLUDE_OPT" = "$(basename ${f})" ]
    then
        gcc "$f" $GCCARGS "-O0" -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
    else
        gcc "$f" $GCCARGS -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
    fi
done

for f in $ASMFILES; do
    nasm "$f" $NASMARGS -o "${OUTDIR}$(basename ${f%.${ASMEXT}}.o)"
done

## Link

echo "Linking..."

OBJ="$(ls ${OUTDIR}*.o)"

ld $LDARGS $OBJ $LIBS -o "${OUTDIR}${KNAME}"

echo "Done!"
