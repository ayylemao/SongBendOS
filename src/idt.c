#include "include/idt.h"
#include "include/vga.h"
#include "include/util.h"
#include "include/log.h"

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];

void exception_handler(uint32_t interrupt_vector, uint32_t error_code) {
    log_stdout(CRITICAL_COLOR, "Processor Exception! Interrupt Vector %d", true, interrupt_vector);

    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    while(1);
}
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void init_Idt() {
    log_stdout(LOG_LEVEL_DEBUG, "Initializing IDT...", false, false);
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    log_stdout(LOG_LEVEL_INFO, "IDT ok!", false, false);
    log_stdout(LOG_LEVEL_DEBUG, "Enabling interupts...", false, false);
    __asm__ volatile ("sti"); // set the interrupt flag
}