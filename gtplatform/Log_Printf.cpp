#include "gtengine/utils/Log.h"

#include <cstdio>


// Implementation shared for Qt, QNX, Linux
namespace gt
{
    inline void print(const char* prefix, const char* format, va_list args)
    {
        printf("%s", prefix);
        vprintf(format, args);
        printf("\n");
        fflush(stdout);
    }

    void Log::print_verbose(const char* format, va_list args) {
        print(GT_LOG_TAG_VERBOSE, format, args);
    }

    void Log::print_debug(const char* format, va_list args) {
        print(GT_LOG_TAG_DEBUG, format, args);
    }

    void Log::print_info(const char* format, va_list args) {
        print(GT_LOG_TAG_INFO, format, args);
    }

    void Log::print_trace(const char* format, va_list args) {
        print(GT_LOG_TAG_TRACE, format, args);
    }

    void Log::print_warning(const char* format, va_list args) {
        print(GT_LOG_TAG_WARN, format, args);
    }

    void Log::print_error(const char* format, va_list args) {
        print(GT_LOG_TAG_ERR, format, args);
    }
}
