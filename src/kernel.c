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

    __asm__ volatile ("cli");
    //uint32_t* ptr = (uint32_t*)0x0;  // Null pointer dereference
    //uint32_t value = *ptr;
    __asm__ volatile ("sti");
};