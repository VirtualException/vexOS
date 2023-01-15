qemu-system-x86_64 -cdrom dist/vexos_uefi.iso \
-drive file=/usr/share/ovmf/x64/OVMF_CODE.fd,if=pflash,format=raw,readonly=on,unit=0 \
-audiodev pa,id=1 -machine pcspk-audiodev=1 -m 256M -smp 5 -enable-kvm \
