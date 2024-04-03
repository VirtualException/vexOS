# vexOS
Amateur x64 Operating System (for UEFI)

## What is it?

This is a basic OS made for x86_64 architectures.
It is made up of 2 parts: the kernel and the bootloader.

To load the kernel it is needed a bootloader (located under the `bootloader/` directory) that uses the UEFI environment for:
 - Setting up video
 - Getting time
 - Loading the kernel from the filesystem
 - Loading a pixel-map font (`font.h`)
 - Starting the kernel execution (calling the `start_kernel()` function)

The vexOS kernel counts with the following features:
 - Video (efi gop driver)
 - Terminal (custom implementation called `vtt`)
 - Keyboard input
 - Interrupt/Exception handling
 - Syscall handling
 - PIC
 - PIT
 - GDT and IDT setup
 - Random number generator
 - Serial output
 - Printf-like family functions
 - SMBIOS (or at least I'm trying)
 - Some random stuff

## Building
**gcc**, **nasm** and **make** are the only tools needed to compile the hole OS.
For the bootloader, the library **gnu-efi** is also needed.


> [!NOTE]
> `gnu-efi` version ` 3.0.18` breaks for some reason some EFI functionality at least on QEMU. I'm trying to understand why and fix it.


In Linux, just run
```
make
```
or run the specific target for every of its parts
```
make kernel
make bootloader
make image
```
To build in debug mode, 
```
make debug
```
Only the kernel will count with debugging features.

The output will be the bootloader (`bootloader/out/BOOTX64.EFI`) and the kernel (`kernel/out/vexos64kernel`).

You can find and iso image already built under the `dist/` directory and a fat image inside `img/`

~~If u want the image and u are a Windows user, just leave.~~

## Testing
There is an script that uses QEMU to run the OS:
```
./run.sh
```
GDB is recommended for debugging.

## License
Fuck private property, this is under **CC0**.

## Screenshots
### Kernel screenshot:
![kernel screenshot](/screenshots/kernel.png)
### Bootloader screenshot (running on qemu):
![bootloader screenshot](/screenshots/bootloader.png)

## Extra
Special thanks to the contributors of [OSDev](https://wiki.osdev.org) and the random person who wrote in it:
> "Sound is never noticed by users, until it isn't there."
