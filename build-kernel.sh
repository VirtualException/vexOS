set -e

KNAME="vexos64kernel"
DEBUG=0
EXCLUDE_OPTIMIZE="kprintf.c"

CEXT="c"
ASMEXT="asm"

SRCDIR="kernel/source/"
OUTDIR="kernel/out/"
INCDIR="kernel/include/"

CFILES="$(find ${SRCDIR} -name \*.${CEXT})"
ASMFILES="$(find ${SRCDIR} -name \*.${ASMEXT})"

# -Ofast is quite clumsy...
GCCARGS="-c -O3
        -Wall -Wextra
        -mtune=native -mfpmath=sse -mmmx -msse -msse2 -msse3 -mssse3 -msse4 -m3dnow
        -ffreestanding -fno-stack-protector -fno-stack-check -fno-builtin -fno-pic -fPIE
        -mno-red-zone -m64"

NASMARGS="-f elf64"
LDARGS="-nostdlib -static -T kernel/link/kernel.ld -no-warn-rwx-segments"

function item_in_list {

    local item="$1"
    local list="$2"

    if [[ $list =~ (^|[[:space:]])"$item"($|[[:space:]]) ]] ; then
        return 0
    else
        return 1
    fi
}

if [ $DEBUG = 1 ]
then
    GCCARGS+=" -g -Og -D__DEBUG__"
    NASMARGS+=" -g"
    LDARGS+=" -g"
fi

tput bold
echo "[Building '${KNAME}']"
tput sgr0

# Compile

echo "Compiling..."

if [ $DEBUG = 1 ]
then
    echo "(debug mode)"
fi

for f in $CFILES; do

    if item_in_list "$(basename ${f})" "$EXCLUDE_OPTIMIZE" ;
    then # DONT DO OPTIMIZATION
        gcc "$f" $GCCARGS -I $INCDIR "-O0"  -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
    else # NORMAL COMPILATION
        gcc "$f" $GCCARGS -I $INCDIR        -o "${OUTDIR}$(basename ${f%.${CEXT}}.o)"
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
