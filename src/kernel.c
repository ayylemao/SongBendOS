#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/util.h"

void kmain(void);

void kmain(void)
{
    __asm__ volatile ("cli");
    initGdt();
    print("GDT has worked!\r\n");
    init_Idt();
    print("IDT has worked!\r\n");

    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    __asm__ volatile ("sti");
};