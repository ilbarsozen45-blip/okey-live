#ifndef ILB_LOG_H
#define ILB_LOG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ilb_log_level {
    ILB_LOG_DEBUG = 0,
    ILB_LOG_INFO,
    ILB_LOG_WARN,
    ILB_LOG_ERROR,
};

void ilb_log_init(void);
void ilb_log_set_level(enum ilb_log_level level);
void ilb_log(enum ilb_log_level level, const char* module, const char* fmt, ...);
void ilb_log_v(enum ilb_log_level level, const char* module, const char* fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif
