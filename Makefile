
BUILD_PATH=build

all: prepare clean build run

prepare:
	mkdir -p $(BUILD_PATH)

boot.o:
	#i686-elf-as boot.s -o boot.o
	nasm -felf32 boot.asm -o $(BUILD_PATH)/boot.o

kernel.o:
	i686-elf-gcc -c kernel.c -o $(BUILD_PATH)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build: boot.o kernel.o
	# i686-elf-gcc -T linker.ld -o $(BUILD_PATH)/os.bin -ffreestlsanding -O2 -nostdlib $(BUILD_PATH)/boot.o $(BUILD_PATH)/kernel.o -lgcc
	i686-elf-gcc -T linker.ld -o $(BUILD_PATH)/os.bin -O2 -nostdlib $(BUILD_PATH)/boot.o $(BUILD_PATH)/kernel.o -lgcc

run: build
	qemu-system-i386 -kernel $(BUILD_PATH)/os.bin

clean:
	rm -rf $(BUILD_PATH)/*
