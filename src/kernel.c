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
    printf("GDT has worked!\r\n");
    init_Idt();
    set_text_color(COLOR8_LIGHT_BLUE);
    printf("IDT has worked!\r\n");

    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);

    log_stdout(LOG_LEVEL_WARN, "abc", false, false);
    log_stdout(LOG_LEVEL_INFO, "Formatting took %x seconds!", true, 9892);

    __asm__ volatile ("sti");
};