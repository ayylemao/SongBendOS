#pragma once
#include "stdint.h"

void *memset(void *dest, char val, uint32_t count);
void itoa(int32_t value, char* buffer, int base);
void ftoa(float value, char* buffer, int precision);
void vprintf(const char* format, void* args);
void printf(const char* format, ...);
void svprintf(char* output_buffer, const char* format, void* args);
void append_to_buffer(char* output_buffer, const char* str, size_t* pos);

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}