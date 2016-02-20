
BUILD_PATH=build
SRC_PATH=src
BOOTLOADER_PATH=$(SRC_PATH)/bootloader
KERNEL_PATH=$(SRC_PATH)/kernel

KERNEL_MODULES = color.o kernel.o term.o string.o integer.o
BUILD_LD = $(KERNEL_MODULES:%=$(BUILD_PATH)/%)

all: prepare clean build run

prepare:
	mkdir -p $(BUILD_PATH)

boot.o:
	#i686-elf-as boot.s -o boot.o
	nasm -felf32 $(BOOTLOADER_PATH)/boot.asm -o $(BUILD_PATH)/boot.o

%.o:
	i686-elf-gcc -c $(KERNEL_PATH)/$*.c -o $(BUILD_PATH)/$*.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build: boot.o $(KERNEL_MODULES)
	# i686-elf-gcc -T linker.ld -o $(BUILD_PATH)/os.bin -ffreestlsanding -O2 -nostdlib $(BUILD_PATH)/boot.o $(BUILD_PATH)/kernel.o -lgcc
	i686-elf-gcc -T $(SRC_PATH)/linker.ld -o $(BUILD_PATH)/os.bin -O2 -nostdlib $(BUILD_PATH)/boot.o $(BUILD_LD) -lgcc

run: build
	qemu-system-i386 -kernel $(BUILD_PATH)/os.bin

clean:
	rm -rf $(BUILD_PATH)/*
