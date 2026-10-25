#include <ml/Log/ModLogger.h>

#include <cstdio>
#include <math/seadMathCalcCommon.h>
#include <ml/Log/LogUtil.h>
#include <ml/Util/Abort.h>
#include <prim/seadScopedLock.h>

namespace ml {

namespace {

constexpr const char* LogFilePath = "sd:/mod-logs.txt"; // could potentially add support for timestamped logs

}

// TODO: Queue logs to separate log write thread

ModLogger::ModLogger() :
    mCriticalSection(nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified)
{

}

void ModLogger::writeLog(const char* format, va_list args) {
    sead::ScopedLock lock(&mCriticalSection);

    int bytesWritten = std::vsnprintf(mBuffer, sizeof(mBuffer), format, args);
    if (bytesWritten <= 0) {
        return;
    }

    // vsnprintf returns the full size that would have been written, even if the result was truncated
    int lineSize = sead::Mathi::min(bytesWritten, sizeof(mBuffer) - 1);
    mBuffer[lineSize] = '\n';

    mDebugLogger.writeLine(std::string_view(mBuffer, lineSize));
    mFileLogger.writeLine(std::string_view(mBuffer, lineSize + 1)); // +1 includes the newline character
    mTcpLogger.writeLine(std::string_view(mBuffer, lineSize + 1));
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

void ModLogger::WriteLog(const char* format, va_list args) {
    ModLogger::Instance()->writeLog(format, args);
}

}
