#include <ml/Log/LogUtil.h>

#include <ml/Log/ModLogger.h>

namespace ml {

LogLevel getLogLevel() {
    return ModLogger::GetLogLevel();
}

void setLogLevel(LogLevel logLevel) {
    ModLogger::SetLogLevel(logLevel);
}

void logLine(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ModLogger::WriteLog(fmt, args);
    va_end(args);
}

void logLeveled(LogLevel logLevel, const char* fmt, ...) {
    if (ModLogger::IsLogLevelEnabled(logLevel)) {
        va_list args;
        va_start(args, fmt);
        ModLogger::WriteLog(fmt, args);
        va_end(args);
    }
}

void logLeveledV(ml::LogLevel logLevel, const char* fmt, va_list args) {
    if (ModLogger::IsLogLevelEnabled(logLevel)) {
        ml::ModLogger::WriteLog(fmt, args);
    }
}

}
