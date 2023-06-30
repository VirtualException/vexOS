# vexOS
Basic x64 Operating System (for UEFI)

## What is it?

This is an amateur OS made for x86_64 architectures.
It is made up of 2 parts: the kernel and the bootloader.

To load the kernel it is needed a bootloader (located under the `bootloader/` directory) that uses UEFI for:
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
 - Serial output
 - Video (efi gop driver)
 - Terminal (custom implementation called `vtt`)
 - Custom pixel-by-pixel font (`font.h`)
 - Printf-like family functions
 - Some random stuff

## Building
**GCC** and **NASM** are the only tools needed to compile the hole OS.
For the bootloader, the library **gnu-efi** is also needed.
In Linux, just run the 
```
./build.sh
```
script, or run the specific script for every of its parts. To build in debug mode, change the option in `build-kernel.sh` from `DEBUG=0` to `DEBUG=1`.

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
### Kernel screenshot:
![kernel screenshot](/screenshots/kernel.png)
### Bootloader screenshot (running on qemu):
![bootloader screenshot](/screenshots/bootloader.png)

## Extra
Special thanks to the contributors of [OSDev](https://wiki.osdev.org) and the random person who wrote:
> "Sound is never noticed by users, until it isn't there."
