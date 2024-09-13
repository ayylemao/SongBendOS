#include "include/util.h"

void *memset(void *dest, char val, uint32_t count)
{
    char *temp = (char*) dest;
    for (; count != 0; count --)
    {
        *temp++ = val;
    }
    return dest;
}

void itoa(int value, char* str, int base) {
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;

    // Handle base validity: this implementation only works for bases 2 to 16
    if (base < 2 || base > 16) {
        *str = '\0';
        return;
    }

    // Handle negative numbers for base 10
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    // Convert the number to the given base
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEF"[tmp_value % base];
    } while (value);

    // Null-terminate the string
    *ptr = '\0';

    // Reverse the string
    while (ptr1 < --ptr) {
        tmp_char = *ptr;
        *ptr = *ptr1;
        *ptr1++ = tmp_char;
    }
}