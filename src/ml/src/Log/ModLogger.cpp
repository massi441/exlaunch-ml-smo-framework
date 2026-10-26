#include <ml/Log/ModLogger.h>

#include <ml/Core/String/StringUtil.h>
#include <ml/Log/DebugPrint.h>
#include <ml/Log/LogUtil.h>
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

void ModLogger::InitializeFile() {
    if (ModLogger::Instance()->mFileLogger.open(LogFilePath)) {
        LOG_INFORMATION("File logger initialized!");
    }
}

void ModLogger::InitializeNetwork() {
    if (ModLogger::Instance()->mTcpLogger.connect("127.0.0.1", 3080)) {
        LOG_INFORMATION("TCP logger initialized!");
    }
}

void ModLogger::SetLogLevel(LogLevel logLevel) {
    ModLogger::Instance()->mLogLevel = logLevel;
}

LogLevel ModLogger::GetLogLevel() {
    return ModLogger::Instance()->mLogLevel;
}

bool ModLogger::IsLogLevelEnabled(LogLevel logLevel) {
    return logLevel >= ModLogger::Instance()->mLogLevel;
}

void ModLogger::WriteLog(const char* fmt, va_list args) {
    ModLogger::Instance()->writeLog(fmt, args);
}

}
