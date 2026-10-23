#include <ml/Util/Abort.h>

#include <basis/seadRawPrint.h>
#include <cstdarg>
#include <cstdio>
#include <ml/Util/Logger.h>

namespace ml {

namespace {

[[noreturn]] void abortV(const char* fmt, va_list args) {
    char message[0x400];
    std::vsnprintf(message, sizeof(message), fmt, args);

    LOG_FATAL("%s", message);
    sead::system::HaltWithDetail(__FILE__, __LINE__, "%s", message);

    UNREACHABLE;
}

}

void Abort(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    abortV(fmt, args);
}

void AbortIf(bool condition, const char* fmt, ...) {
    if (!condition) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    abortV(fmt, args);
}

void AbortIfNot(bool condition, const char* fmt, ...) {
    if (condition) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    abortV(fmt, args);
}

}
