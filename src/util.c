#include "include/util.h"
#include "include/stdint.h"
#include "include/vga.h"
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

// Convert an integer to a string (base 10)
void itoa(int32_t value, char* buffer, int base)
{
    char* ptr = buffer;
    bool negative = false;

    // Handle negative numbers for base 10
    if (value < 0 && base == 10)
    {
        negative = true;
        value = -value;
    }

    // Convert the integer to a string in reverse order
    do
    {
        int digit = value % base;
        *ptr++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value /= base;
    } while (value > 0);

    // Add minus sign if needed
    if (negative)
    {
        *ptr++ = '-';
    }

    // Null-terminate the string
    *ptr = '\0';

    // Reverse the string
    for (char* left = buffer, *right = ptr - 1; left < right; left++, right--)
    {
        char temp = *left;
        *left = *right;
        *right = temp;
    }
}

// Convert a float to a string
void ftoa(float value, char* buffer, int precision)
{
    if (value < 0)
    {
        *buffer++ = '-';
        value = -value;
    }

    int32_t intPart = (int32_t)value;
    itoa(intPart, buffer, 10);

    // Move pointer to the end of the integer part
    while (*buffer != '\0') buffer++;

    *buffer++ = '.';

    // Convert fractional part
    float fractionalPart = value - (float)intPart;
    for (int i = 0; i < precision; i++)
    {
        fractionalPart *= 10;
        int32_t digit = (int32_t)fractionalPart;
        *buffer++ = '0' + digit;
        fractionalPart -= digit;
    }

    *buffer = '\0';
}

void vprintf(const char* format, void* args)
{
    char* arg_ptr = (char*)args; // The pointer to the first argument

    while (*format)
    {
        if (*format == '%')
        {
            format++;  // Skip '%'
            switch (*format)
            {
                case 'd': // Integer
                {
                    int32_t i = *((int32_t*)arg_ptr);
                    arg_ptr += sizeof(int32_t); // Move to the next argument
                    char buffer[16];
                    itoa(i, buffer, 10);
                    print(buffer);
                    break;
                }
                case 'x': // Hexadecimal
                {
                    int32_t i = *((int32_t*)arg_ptr);
                    arg_ptr += sizeof(int32_t);
                    char buffer[16];
                    itoa(i, buffer, 16);
                    print("0x");
                    print(buffer);
                    break;
                }
                case 'f': // Float
                {
                    double f = *((double*)arg_ptr); // floats are promoted to double
                    arg_ptr += sizeof(double);
                    char buffer[32];
                    ftoa((float)f, buffer, 6); // 6 digits of precision
                    print(buffer);
                    break;
                }
                case 's': // String
                {
                    const char* s = *((const char**)arg_ptr);
                    arg_ptr += sizeof(const char*);
                    print(s);
                    break;
                }
                case 'c': // Character
                {
                    char c = *((char*)arg_ptr);
                    arg_ptr += sizeof(int); // char is passed as int in variadic functions
                    char buffer[2] = {c, '\0'};
                    print(buffer);
                    break;
                }
                case '%': // Literal '%'
                {
                    print("%");
                    break;
                }
                default:
                    print("%");
                    print((const char[]){*format, '\0'});
                    break;
            }
        }
        else
        {
            // Print a regular character
            char buffer[2] = {*format, '\0'};
            print(buffer);
        }
        format++;
    }
}

void printf(const char* format, ...)
{
    // The variadic arguments are passed after the format string, so we get the address of the first argument.
    void* first_arg = (void*)(&format + 1);
    vprintf(format, first_arg);
}

