set -e

tput bold
echo "[Building iso file]"
tput sgr0

# Create a fat .img file, with EFI dir & boot application
dd if=/dev/zero of=img/vexos_uefi.img bs=1k count=1440 > /dev/null 2>&1
mformat -i img/vexos_uefi.img -f 1440 ::
mmd -i img/vexos_uefi.img ::/EFI
mmd -i img/vexos_uefi.img ::/EFI/BOOT
mcopy -i img/vexos_uefi.img bootloader/out/BOOTX64.EFI ::/EFI/BOOT
mcopy -i img/vexos_uefi.img kernel/out/vexos64kernel ::/

# Create final iso file
sudo xorriso -as mkisofs -R -f -e vexos_uefi.img -o dist/vexos_uefi.iso img -no-emul-boot> /dev/null 2>&1

echo "Done!"