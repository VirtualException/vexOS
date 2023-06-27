# vexOS
Basic x64 Operating System (for UEFI)

## What is it?

This is an amateur OS made for x86_64 architectures.
It is made up of 2 parts: the kernel and the bootloader.

For loading the kernel its needed a bootloader (located under the `bootloader/` directory) that uses UEFI for:
 - Setting up video
 - Getting time
 - Loading the kernel from the filesystem
 - Starting the kernel execution (calling the `StartKernel` function)

The vexOS kernel counts with the following features:
 - GDT and IDT setup
 - Interrupt/Exception handling
 - Syscall handling
 - PIC
 - PIT
 - Keyboard input
 - Random number generator
 - Serial input
 - Video (efi gop driver)
 - Terminal (custom implementation called `vtt`)
 - Custom pixel-by-pixel font (`ter10x16.h`)
 - Printf-like family functions
 - More random stuff

## Building
**GCC** and **NASM** are the only tools needed to compile the hole OS.
For the bootloader, the library **gnu-efi** is also needed.
In Linux, just run the 
```
./build.sh
```
script, or run the specific script for every of its parts. Change the option in `build-kernel.sh` from `DEBUG=0` to `DEBUG=1` for debug mode.

The output will be the bootloader (`bootloader/out/BOOTX64.EFI`) and the kernel (`kernel/out/vexos64kernel`).

~~If you are a Windows user, just leave.~~

You can find and iso image already built under the `dist/` directory and a fat image inside `img/`

## Testing
There is an script that uses QEMU to run the OS:
```
./run.sh
```
GDB is recommended for debugging.

## License
Fuck private property, this is under **CC0**.

## Screenshots
### Kernel screenshot (wrapped):
![kernel screenshot](/screenshots/kernel.png)
### Bootloader screenshot (unwraped):
![bootloader screenshot](/screenshots/bootloader.png)

## Extra
Special thanks to the contributors of wiki.osdev.org and the random person who wrote:
> "Sound is never noticed by users, until it isn't there."