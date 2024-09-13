#pragma once
#include "stdint.h"

void *memset(void *dest, char val, uint32_t count);
void itoa(int value, char* str, int base);