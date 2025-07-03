#include "gtengine/utils/Log.h"

#include <cstdio>

namespace gt
{
    void Log::write(Level, const char* prefix, const char* format, va_list argptr)
    {
        printf(prefix);
        vprintf(format, argptr);
        printf("\n");
        fflush(stdout);
    }
}
