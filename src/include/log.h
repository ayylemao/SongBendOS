#include "stdint.h"

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_CRITICAL 5

#define LOG_LEVEL LOG_LEVEL_DEBUG

#define DEBUG_M "[DEBUG]\t\t"
#define INFO_M "[INFO]\t\t"
#define WARN_M "[WARNING]\t\t"
#define ERROR_M "[ERROR]\t\t"
#define CRITICAL_M "[CRITICAL]\t\t"

#define DEBUG_COLOR COLOR8_LIGHT_GREY
#define INFO_COLOR COLOR8_LIGHT_GREEN
#define WARN_COLOR COLOR8_YELLOW
#define ERROR_COLOR COLOR8_RED
#define CRITICAL_COLOR COLOR8_RED

void log_stdout(uint8_t level, char* message_fmt, bool format_flag, uint32_t to_format);
