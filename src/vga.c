#include "include/vga.h"

uint16_t column = 0;
uint16_t line = 0; 
uint16_t* const vga = (uint16_t* const) 0xB8000;
const uint16_t defaultColor = (COLOR8_BLACK << 8) | (COLOR8_LIGHT_GREY << 12);
const uint16_t backgroundBlack = (COLOR8_BLACK << 12);  // Background is always black
const uint16_t defaultForegroundColor = (COLOR8_LIGHT_GREY << 8); // Default foreground color
uint16_t currentForegroundColor = defaultForegroundColor;
uint16_t currentColor = defaultColor;

void Reset()
{
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga[y * width + x] = ' ' | defaultColor;
        }
    }
}

void newLine()
{
    if (line < height - 1)
    {
        line++;
        column = 0;
    }
    else
    {
        scrollUp();
        column = 0;
    }
}

void scrollUp()
{
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga[(y-1) * width + x] = vga[y*width+x];
        }
    }

    for (uint16_t x = 0; x < width; x++)
    {
        vga[(height-1) * width + x] = ' ' | currentColor;
    }
}

void set_text_color(uint16_t color)
{
    currentForegroundColor = (color << 8);  // Only set the foreground color
}

void print(const char* s)
{
    while (*s)
    {
        switch(*s)
        {
            case '\n':
                newLine();
                break;
            case '\r':
                column = 0;
                break;
            case '\t':
                if (column == width)
                {
                    newLine();
                }
                uint16_t tabLen = 4 - (column % 4);
                while (tabLen != 0)
                {
                    // Write space with current foreground and black background
                    vga[line * width + (column++)] = ' ' | backgroundBlack | currentForegroundColor;
                    tabLen--;
                }
                break;
            default:
                if (column == width)
                {
                    newLine();
                }
                // Combine current foreground color with black background for each character
                vga[line * width + (column++)] = *s | backgroundBlack | currentForegroundColor;
                break;
        }
        s++;
    }
}
