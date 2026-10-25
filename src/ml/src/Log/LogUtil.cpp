#include <ml/Log/LogUtil.h>

#include <ml/Log/GlobalLogger.h>

namespace ml {

LogLevel getLogLevel() {
    return GlobalLogger::GetLogLevel();
}

void setLogLevel(LogLevel logLevel) {
    GlobalLogger::SetLogLevel(logLevel);
}

void logLine(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GlobalLogger::WriteLog(fmt, args);
    va_end(args);
}

void logLeveled(LogLevel logLevel, const char* fmt, ...) {
    if (GlobalLogger::IsLogLevelEnabled(logLevel)) {
        va_list args;
        va_start(args, fmt);
        GlobalLogger::WriteLog(fmt, args);
        va_end(args);
    }
}

void logLeveledV(ml::LogLevel logLevel, const char* fmt, va_list args) {
    if (GlobalLogger::IsLogLevelEnabled(logLevel)) {
        ml::GlobalLogger::WriteLog(fmt, args);
    }
}

}
