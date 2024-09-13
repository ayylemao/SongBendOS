#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"

void kmain(void);
static inline void outb(uint16_t port, uint8_t value);
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
void disable_all_irqs();
void disable_all_irqs() {
    // Mask all IRQs (disable all hardware interrupts)
    outb(0x21, 0xFF);  // Mask all IRQs on the master PIC
    outb(0xA1, 0xFF);  // Mask all IRQs on the slave PIC
}

void trigger_double_fault() {
    // Corrupt the stack pointer
    __asm__ volatile ("mov $0x0, %esp");  // Set ESP to an invalid value
    
    // Trigger a divide-by-zero (or any other exception)
    uint32_t zero = 0;
    uint32_t result = 1 / zero;  // This will cause a divide-by-zero exception (vector 0)
}

void kmain(void)
{
    initGdt();
    print("GDT has worked!\r\n");
    init_Idt();
    print("IDT has worked!\r\n");
    __asm__ volatile ("cli");
    disable_all_irqs();
    //uint32_t* ptr = (uint32_t*)0x0;  // Null pointer dereference
    //uint32_t value = *ptr;
    __asm__ volatile ("ljmp $0x28, $0x0");  // Jump to an invalid TSS selector (vector 10)
};