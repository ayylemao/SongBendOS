
CFLAGS = -fno-stack-protector -fno-builtin -Wall -g -nostdinc
BUILD = build
CC = /home/matthias/opt/cross/bin/i686-elf-gcc
LD = /home/matthias/opt/cross/bin/i686-elf-ld


all: clean kernel boot image

kernel:
	$(CC) $(CFLAGS) -c src/kernel.c -o $(BUILD)/kernel.o
	$(CC) $(CFLAGS) -c src/vga.c -o $(BUILD)/vga.o
	$(CC) $(CFLAGS) -c src/gdt.c -o $(BUILD)/gdt.o
	$(CC) $(CFLAGS) -c src/util.c -o $(BUILD)/utils.o

boot:
	nasm -f elf32 src/boot.s -o $(BUILD)/boot.o
	nasm -f elf32 src/gdt.s -o $(BUILD)/gdts.o

image:
	$(LD) -m elf_i386 -T linker.ld -o SB/boot/kernel $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/vga.o $(BUILD)/gdt.o $(BUILD)/gdts.o $(BUILD)/utils.o
	grub-mkrescue -o sb.iso SB/

clean: 
	rm -rf $(BUILD)/*
	rm -rf SB/boot/kernel
	rm -rf *.iso