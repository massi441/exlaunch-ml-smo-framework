#include <ml/Log/GlobalLogger.h>

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

GlobalLogger::GlobalLogger() :
    mCriticalSection(nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified)
{

}

void GlobalLogger::writeLog(const char* format, va_list args) {
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
}

void GlobalLogger::Initialize() {
    if (GlobalLogger::Instance()->mFileLogger.open(LogFilePath)) {
        LOG_INFORMATION("File logger initialized!");
    }
}

void GlobalLogger::SetLogLevel(LogLevel logLevel) {
    GlobalLogger::Instance()->mLogLevel = logLevel;
}

LogLevel GlobalLogger::GetLogLevel() {
    return GlobalLogger::Instance()->mLogLevel;
}

bool GlobalLogger::IsLogLevelEnabled(LogLevel logLevel) {
    return logLevel >= GlobalLogger::Instance()->mLogLevel;
}

void GlobalLogger::WriteLog(const char* format, va_list args) {
    GlobalLogger::Instance()->writeLog(format, args);
}

}
