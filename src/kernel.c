#include "include/vga.h"
#include "include/gdt.h"

void kmain(void);

void kmain(void)
{
    initGdt();
    print("GDT has worked!\r\n");
};