#include "ilb/log.h"
#include <stdio.h>

static enum ilb_log_level g_level = ILB_LOG_DEBUG;

void ilb_log_init(void) {
    g_level = ILB_LOG_DEBUG;
}

void ilb_log_set_level(enum ilb_log_level level) {
    g_level = level;
}

static const char* level_name(enum ilb_log_level level) {
    switch (level) {
        case ILB_LOG_DEBUG: return "DEBUG";
        case ILB_LOG_INFO: return "INFO";
        case ILB_LOG_WARN: return "WARN";
        case ILB_LOG_ERROR: return "ERROR";
        default: return "UNK";
    }
}

void ilb_log_v(enum ilb_log_level level, const char* module, const char* fmt, va_list ap) {
    if (level < g_level) return;
    fprintf(stderr, "[%s][%s] ", level_name(level), module ? module : "core");
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
}

void ilb_log(enum ilb_log_level level, const char* module, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    ilb_log_v(level, module, fmt, ap);
    va_end(ap);
}
