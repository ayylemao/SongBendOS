#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"

void kmain(void);


void kmain(void)
{
    initGdt();
    print("GDT has worked!\r\n");
    init_Idt();
    print("IDT has worked!\r\n");
    //__asm__ volatile ("sti");
};