.PHONY: kernel bootloader

all: kernel bootloader image

kernel:
	cd ./kernel && $(MAKE)

bootloader:
	cd ./bootloader && $(MAKE)

debug: bootloader
	cd ./kernel && $(MAKE) debug
	$(MAKE) image


# Create iso image
image:
	$(info Building iso file)

	dd if=/dev/zero of=img/vexos_uefi.img bs=1k count=1440 > /dev/null 2>&1
	mformat -i img/vexos_uefi.img -f 1440 ::
	mmd -i img/vexos_uefi.img ::/EFI
	mmd -i img/vexos_uefi.img ::/EFI/BOOT
	mcopy -i img/vexos_uefi.img bootloader/out/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i img/vexos_uefi.img kernel/out/vexos64kernel ::/

	sudo xorriso -as mkisofs -R -f -e vexos_uefi.img -o dist/vexos_uefi.iso img -no-emul-boot> /dev/null 2>&1

clean:
	cd kernel && $(MAKE) clean
	cd bootloader && $(MAKE) clean
