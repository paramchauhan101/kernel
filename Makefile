# Makefile for a simple OS with a bootloader and kernel

# Targets
all: os-image

# Combine bootloader and kernel into a single image
os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image

# Assemble the bootloader
boot.bin: boot.asm
	nasm -f bin -o boot.bin boot.asm

# Compile and link the kernel
kernel.bin: kernel.o
	objcopy -O binary kernel.o kernel.bin

kernel.o: kernel.c
	gcc -ffreestanding -o kernel.o -c kernel.c

# Clean up generated files
clean:
	rm -f *.bin *.o os-image
