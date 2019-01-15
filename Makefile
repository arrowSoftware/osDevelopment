# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS   = $(wildcard kernel/*.h drivers/*.h)
OBJECTS   = ${C_SOURCES:.c=.o}
CC        = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD        = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB       = /usr/local/i386elfgcc/bin/i386-elf-gdb
QEMU      = qemu-system-i386
# -g for debugging symbols.
CFLAGS    = -g
NASM      = nasm

os-image.bin: boot/bootSector.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deleted all symbols as a collateral, so we dont need to
# strip them menually.
kernel.bin: boot/kernelEntry.o ${OBJECTS}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# used for debugging
kernel.elf: boot/kernelEntry.o ${OBJECTS}
	$(LD) -o $@ -Ttext 0x1000 $^

run: os-image.bin
	$(QEMU) -fda os-image.bin

# open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	$(QEMU) -s -fda os-image.bin &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	$(NASM) $< -f elf -o $@

%.bin: %.asm
	$(NASM) $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
