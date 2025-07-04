#include "gtengine/utils/Log.h"

#include <cstdio>
#include <stdarg.h>

namespace gt
{
    void write(Log::Level, const char* prefix, const char* format, va_list argptr)
    {
        printf(prefix);
        vprintf(format, argptr);
        printf("\n");
        fflush(stdout);
    }

    void Log::debug(const char* format, ...)
    {
        if (show(Log::DEBUG))
        {
            va_list argptr;
            va_start(argptr, format);
            write(Log::DEBUG, "(GT DEBUG) ", format, argptr);
            va_end(argptr);
        }
    }

    void Log::info(const char* format, ...)
    {
        if (show(Log::INFO))
        {
            va_list argptr;
            va_start(argptr, format);
            write(Log::INFO, "(GT INFO) ", format, argptr);
            va_end(argptr);
        }
    }

    void Log::trace(const char* format, ...)
    {
        if (show(Log::TRACE))
        {
            va_list argptr;
            va_start(argptr, format);
            write(Log::TRACE, "(GT TRACE) ", format, argptr);
            va_end(argptr);
        }
    }

    void Log::warning(const char* format, ...)
    {
        if (show(Log::WARN))
        {
            va_list argptr;
            va_start(argptr, format);
            write(Log::WARN, "(GT WARN) ", format, argptr);
            va_end(argptr);
        }
    }

    void Log::error(const char* format, ...)
    {
        if (show(Log::ERR))
        {
            va_list argptr;
            va_start(argptr, format);
            write(Log::ERR, "(GT ERR) ", format, argptr);
            va_end(argptr);
        }
    }
}
