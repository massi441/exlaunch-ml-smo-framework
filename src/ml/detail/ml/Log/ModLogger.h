#pragma once

#include <ml/Log/LogLevel.h>
#include <ml/Log/Loggers.h>
#include <thread/seadCriticalSection.h>

namespace ml {

/**
 * Formats and forwards log calls to all its loggers with thread safety.
 */
class ModLogger final {
    NO_COPY_NO_MOVE(ModLogger)
public:
    /**
     * Initializes the file logger
     */
    static void InitializeFile();

    /**
     * Initializes the TCP logger
     */
    static void InitializeNetwork();

    /**
     * Logs a formatted message to all initialized loggers
     */
    static void WriteLog(const char* fmt, va_list args);

    static void SetLogLevel(LogLevel logLevel);

    static LogLevel GetLogLevel();

    static bool IsLogLevelEnabled(LogLevel logLevel);

private:
    char mBuffer[1024] = {}; // potentially use ml::Array<char> and inject size into it
    sead::CriticalSection mCriticalSection;
    FileLogger mFileLogger;
    TcpLogger mTcpLogger;
    LogLevel mLogLevel;

    void writeLog(const char* format, va_list args);

    static ModLogger* Instance() {
        static ModLogger instance;
        return &instance;
    }

    ModLogger();
};

}
