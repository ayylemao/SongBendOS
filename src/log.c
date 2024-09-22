#include "include/log.h"
#include "include/vga.h"
#include "include/util.h"


void log_stdout(uint8_t level, char *message_fmt, bool format_flag, uint32_t to_format)
{
    const char* log_prefix = NULL;

    switch (level)
    {
    case LOG_LEVEL_DEBUG:
        log_prefix = DEBUG_M;
        set_text_color(DEBUG_COLOR);
        break;
    case LOG_LEVEL_INFO:
        log_prefix = INFO_M;
        set_text_color(INFO_COLOR);
        break;
    case LOG_LEVEL_WARN:
        log_prefix = WARN_M;
        set_text_color(WARN_COLOR);
        break;
    case LOG_LEVEL_ERROR:
        log_prefix = ERROR_M;
        set_text_color(ERROR_COLOR);
        break;
    case LOG_LEVEL_CRITICAL:
        log_prefix = CRITICAL_M;
        set_text_color(CRITICAL_COLOR);
        break;
    default:
        log_prefix = "[UNKNOWN] ";
        set_text_color(DEBUG_COLOR);
        break;
    }

    printf("%s", log_prefix);
    set_text_color(DEFAULT_COLOR);
    if (format_flag == false)
    {
        printf(message_fmt);
        printf("\n");
    }
    else
    {
        printf(message_fmt, to_format);
        printf("\n");
    }
}