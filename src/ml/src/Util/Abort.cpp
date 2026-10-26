#include <ml/Util/Abort.h>

#include <basis/seadRawPrint.h>
#include <ml/Core/String/StringUtil.h>
#include <ml/Log/DebugPrint.h>

namespace ml {

namespace {

[[noreturn]] void abortV(const char* fmt, va_list args) {
    char message[0x400];
    int messageLength = ml::vsnprintf(message, sizeof(message), fmt, args);

    ml::svcPrint(message, messageLength);
    sead::system::HaltWithDetail(__FILE__, __LINE__, "%s", message);

    __builtin_unreachable();
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
