#pragma once

#include <ml/Log/LogLevel.h>
#include <ml/Log/Loggers.h>
#include <thread/seadCriticalSection.h>

namespace ml {

/**
 * Formats and forwards log calls to all its loggers.
 * Is thread safe.
 */
class GlobalLogger final {
    NO_COPY_NO_MOVE(GlobalLogger)
public:
    static void Initialize();
    static void WriteLog(const char* format, va_list args);
    static void SetLogLevel(LogLevel logLevel);
    static LogLevel GetLogLevel();
    static bool IsLogLevelEnabled(LogLevel logLevel);

private:
    char mBuffer[1024] = {}; // potentially use ml::Array<char> and inject size into it
    sead::CriticalSection mCriticalSection;
    DebugLogger mDebugLogger;
    FileLogger mFileLogger;
    LogLevel mLogLevel;

    void writeLog(const char* format, va_list args);

    static GlobalLogger* Instance() {
        static GlobalLogger instance;
        return &instance;
    }

    GlobalLogger();
};

}
