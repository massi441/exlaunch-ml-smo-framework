#include <ml/Log/DebugPrint.h>

#include <exl/nx/kernel/svc.h>
#include <ml/Core/String/StringUtil.h>

namespace ml {

void svcPrint(const char* message, size_t messageSize) {
    svcOutputDebugString(message, messageSize);
}

void svcPrintFmt(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ml::svcPrintFmtV(fmt, args);
    va_end(args);
}

void svcPrintFmtV(const char* fmt, va_list args) {
    constexpr int bufferSize = 1024;
    char buffer[bufferSize];
    int length = ml::vsnprintf(buffer, bufferSize, fmt, args);
    svcOutputDebugString(buffer, length);
}

}
