qemu-system-x86_64 -bios /usr/share/ovmf/x64/OVMF.fd -cdrom dist/vexos_uefi.iso \
-audiodev pa,id=1 -machine pcspk-audiodev=1 -m 512M
