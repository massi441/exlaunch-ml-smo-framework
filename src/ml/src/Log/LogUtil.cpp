#include <ml/Log/Log.h>

#include <ml/Log/ModLogger.h>

namespace ml {

LogLevel getLogLevel() {
    return ModLogger::Instance()->getLogLevel();
}

void setLogLevel(LogLevel logLevel) {
    ModLogger::Instance()->setLogLevel(logLevel);
}

void logLineImpl(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ModLogger::Instance()->writeLog(fmt, args);
    va_end(args);
}

void logLeveledImpl(LogLevel logLevel, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ModLogger::Instance()->writeLog(logLevel, fmt, args);
    va_end(args);
}

void logLeveledV(ml::LogLevel logLevel, const char* fmt, va_list args) {
    ModLogger::Instance()->writeLog(logLevel, fmt, args);
}

}
