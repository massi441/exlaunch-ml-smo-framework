#include <ml/Log/ModLogger.h>

#include <ml/Core/String/StringUtil.h>
#include <ml/Log/DebugPrint.h>
#include <ml/Log/Log.h>
#include <prim/seadScopedLock.h>

namespace ml {

namespace {

constexpr const char* LogFilePath = "sd:/logs.txt"; // could potentially add support for timestamped logs

}

// TODO: Queue logs to separate log write thread

ModLogger::ModLogger() :
    mCriticalSection(nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified)
{
    mTcpLogger = TcpLogger();
    mLogLevel = LogLevel::Debug;
}

void ModLogger::writeLog(const char* format, va_list args) {
    sead::ScopedLock lock(&mCriticalSection);

    int lineSize = ml::vsnprintf(mBuffer, sizeof(mBuffer), format, args);
    if (lineSize <= 0) {
        return;
    }

    mBuffer[lineSize] = '\n';

    ml::svcPrint(mBuffer, lineSize); // debug print, emulators already add a new line to the log

    std::string_view line = std::string_view(mBuffer, lineSize + 1); // +1 includes the newline character

    mFileLogger.writeLine(line);
    mTcpLogger.writeLine(line);
}

void ModLogger::writeLog(LogLevel logLevel, const char* format, va_list args) {
    if (this->isLogLevelEnabled(logLevel)) {
        this->writeLog(format, args);
    }
}

void ModLogger::initializeFile() {
    if (mFileLogger.open(LogFilePath)) {
        LOG_INFORMATION("File logger initialized!");
    }
}

void ModLogger::initializeNetwork() {
    if (mTcpLogger.connect("127.0.0.1", 3080)) {
        LOG_INFORMATION("TCP logger initialized!");
    }
}

void ModLogger::setLogLevel(LogLevel logLevel) {
    mLogLevel = logLevel;

    LOG_LINE("Set log level to %s", ml::LogLevelData::ToString(logLevel));
}

LogLevel ModLogger::getLogLevel() const {
    return mLogLevel;
}

bool ModLogger::isLogLevelEnabled(LogLevel logLevel) const {
    return logLevel >= mLogLevel;
}

}
