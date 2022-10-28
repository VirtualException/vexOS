mount_efi
cp bootloader/out/BOOTX64.EFI /boot/efi/EFI/VEX/OSVX_64.EFI
cp kernel/out/osvx64kernel /boot/efi/osvx64kernel
umount /boot/efi