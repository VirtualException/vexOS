set -e

KNAME="vexos64kernel"

EXCLUDE_OPT="printk.c"
EXCLUDE_SSE="interrupt.c"

CEXT="c"
ASMEXT="asm"

SRCDIR="kernel/source/"
OUTDIR="kernel/out/"

CFILES="$(find ${SRCDIR} -name \*.${CEXT})"
ASMFILES="$(find ${SRCDIR} -name \*.${ASMEXT})"

GCCARGS="-c -O3 -Wall -Wextra -fno-stack-protector -fno-stack-check -fno-builtin -fno-pic -fPIE -mno-red-zone -m64 -I kernel/include"
NASMARGS="-f elf64 -Ox"
LDARGS="-nostdlib -static -T kernel/link/kernel.ld"

tput bold
echo "[Building '${KNAME}']"
tput sgr0

# Compile

echo "Compiling..."

for f in $CFILES; do

    if [ "$EXCLUDE_OPT" = "$(basename ${f})" ]
    then # DONT DO OPTIMIZATION
        gcc "$f" $GCCARGS "-O0" -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"

    elif [ "$EXCLUDE_SSE" = "$(basename ${f})" ]
    then # DONT RELY ON SSE
        gcc "$f" $GCCARGS "-mgeneral-regs-only" -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"

    else # NORMAL COMPILATION
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
