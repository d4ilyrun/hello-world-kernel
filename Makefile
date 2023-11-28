# Toolchain for x86
CC ?= i686-elf-gcc

CFLAGS 		= -std=c99 -Wall -Werror -Wextra -pedantic -ffreestanding
CPPFLAGS 	= -DSTACK_SIZE=16384 -I./include
LDFLAGS 	= -T ./linker.ld -nostdlib

KERNEL_BIN = kernel.bin
KERNEL_ISO = kernel.iso

OBJS = src/crt0.o src/kernel.o

all: iso

kernel: $(KERNEL_BIN)
$(KERNEL_BIN): $(OBJS)
	i686-elf-ld $^ -o $@ $(LDFLAGS)

iso: $(KERNEL_ISO)
$(KERNEL_ISO): $(KERNEL_BIN)
	./scripts/generate_iso.sh $(KERNEL_BIN) $(KERNEL_ISO)

qemu: $(KERNEL_ISO)
	@clear
	qemu-system-i386 -cdrom $(KERNEL_ISO)

clean:
	$(RM) $(OBJS) $(KERNEL_ISO) $(KERNEL_BIN)

.PHONY: clean iso kernel all qemu
