mount_efi
cp bootloader/out/BOOTX64.EFI /boot/efi/EFI/VEX/OSVX_64.EFI
cp kernel/out/vexos64kernel /boot/efi/vexos64kernel
umount /boot/efi
