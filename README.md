NetBSD-lm32_init
================

This is the /sbin/init static sample program for NetBSD/lm32 bring up purpose

If your system uses BSD make, please use gmake (GNU make) command.

To compile and install this /sbin/init into your already generated kernel ELF please do:

$ cd edgebsd-src # Go to the root dir of NetBSD or EdgeBSD src

$ make -C init_src clean init install

By default it will try to insert the ramdisk into the GENERIC_MFS kernel, you can select another kernel by providing the "kernel" variable like this:

$ make -C init_src kernel=GENERIC clean init install

Also, by default it will try to insert the ramdisk into the kernel ELF without debugging symbols ("netbsd"), and not the "netbsd.gdb" one.

To use the "netbsd.gdb" one, please provide the debug=1 variable to make:

$ make -C init_src debug=1 clean init install
