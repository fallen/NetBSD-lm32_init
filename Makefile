ifeq ($(TOOLCHAIN_DIR),)
$(warning WARNING: Using default toolchain for Mac OS X, for something else please provide TOOLCHAIN_DIR variable)
endif

TOPDIR = $(PWD)
TOOLCHAIN_DIR ?= $(TOPDIR)/obj/tooldir.Darwin-10.8.0-i386/
CROSSTC ?= $(TOOLCHAIN_DIR)/bin/lm32--netbsd-
CC = $(CROSSTC)gcc
LD = $(CROSSTC)ld
AS = $(CROSSTC)as
MDSETIMAGE = $(CROSSTC)mdsetimage
DD = dd
NBMAKEFS = $(TOOLCHAIN_DIR)/bin/nbmakefs
RM ?= rm -f
kernel ?= GENERIC_MFS
LDFLAGS ?= -e main -T init.ldscript

ifeq ($(debug),1)
kernel_name = netbsd.gdb
else
kernel_name = netbsd
endif

all init: init.o ident.o
	$(LD) $(LDFLAGS) $^ -o $@

init.o: init.c
	$(CC) -c $^

install: init
	$(DD) if=/dev/zero of=milkymist_disk.ffs bs=1m count=1
	$(RM) -r rootfs
	mkdir -p rootfs/sbin
	cp init rootfs/sbin/
	$(NBMAKEFS) -s 1m milkymist_disk.ffs rootfs
	$(MDSETIMAGE) $(TOPDIR)/sys/arch/milkymist/compile/obj/$(kernel)/$(kernel_name) milkymist_disk.ffs

clean:
	$(RM) -r rootfs
	$(RM) init.o init milkymist_disk.ffs

.PHONY: install clean all
