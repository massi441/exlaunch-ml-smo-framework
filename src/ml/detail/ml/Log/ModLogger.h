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
    static ModLogger* Instance() {
        static ModLogger instance;
        return &instance;
    }

    /**
     * Initializes the file logger
     */
    void initializeFile();

    /**
     * Initializes the TCP logger
     */
    void initializeNetwork();

    /**
     * Formats and logs a message with all initialized loggers
     */
    void writeLog(const char* format, va_list args);

    void setLogLevel(LogLevel logLevel);

    LogLevel getLogLevel() const;

    bool isLogLevelEnabled(LogLevel logLevel) const;

private:
    char mBuffer[1024] = {}; // potentially use ml::Array<char> and inject size into it
    sead::CriticalSection mCriticalSection;
    FileLogger mFileLogger;
    TcpLogger mTcpLogger;
    LogLevel mLogLevel;

    ModLogger();
};

}
