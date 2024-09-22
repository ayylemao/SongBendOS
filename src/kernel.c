#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/util.h"
#include "include/log.h"

void kmain(void);

void kmain(void)
{
    __asm__ volatile ("cli");
    initGdt();
    init_Idt();

    //outb(0x21, 0xFF);
    //outb(0xA1, 0xFF);
};