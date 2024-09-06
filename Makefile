
CFLAGS = -m32 -fno-stack-protector -fno-builtin
BUILD = build

all: clean kernel boot image

kernel:
	gcc $(CFLAGS) -c src/kernel.c -o $(BUILD)/kernel.o

boot:
	nasm -f elf32 src/boot.s -o $(BUILD)/boot.o

image:
	ld -m elf_i386 -T linker.ld -o SB/boot/kernel $(BUILD)/boot.o $(BUILD)/kernel.o
	grub-mkrescue -o sb.iso SB/

clean: 
	rm -rf $(BUILD)/*
	rm -rf SB/boot/kernel