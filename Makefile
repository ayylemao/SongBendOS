
CFLAGS = -m32 -fno-stack-protector -fno-builtin -Wall -g -nostdinc
BUILD = build

all: clean kernel boot image

kernel:
	gcc $(CFLAGS) -c src/kernel.c -o $(BUILD)/kernel.o
	gcc $(CFLAGS) -c src/vga.c -o $(BUILD)/vga.o
	gcc $(CFLAGS) -c src/gdt.c -o $(BUILD)/gdt.o
	gcc $(CFLAGS) -c src/util.c -o $(BUILD)/utils.o

boot:
	nasm -f elf32 src/boot.s -o $(BUILD)/boot.o
	nasm -f elf32 src/gdt.s -o $(BUILD)/gdts.o

image:
	ld -m elf_i386 -T linker.ld -o SB/boot/kernel $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/vga.o $(BUILD)/gdt.o $(BUILD)/gdts.o $(BUILD)/utils.o
	grub-mkrescue -o sb.iso SB/

clean: 
	rm -rf $(BUILD)/*
	rm -rf SB/boot/kernel
	rm -rf *.iso