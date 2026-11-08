#pragma once

#include <cstdarg>
#include <ml/Export.h>
#include <ml/Log/LogLevel.h>

ML_EXPORT_SCOPE_BEGIN

namespace ml {

/**
 * Returns the current log level of the mod logger
 */
LogLevel getLogLevel();

/**
 * Sets the current log level of the mod logger.
 * @param logLevel The new level of logging
 */
void setLogLevel(LogLevel logLevel);

void logLineImpl(const char* fmt, ...);

void logLeveledImpl(ml::LogLevel logLevel, const char* fmt, ...);
void logLeveledV(ml::LogLevel logLevel, const char* fmt, va_list args);

}

ML_EXPORT_SCOPE_END

#ifdef ML_ENABLE_LOG
#define LOG_LINE(fmt, ...)        ml::logLineImpl(fmt, ##__VA_ARGS__)
#define LOG_VERBOSE(fmt, ...)     ml::logLeveledImpl(ml::LogLevel::Verbose, "|V| " fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)       ml::logLeveledImpl(ml::LogLevel::Trace, "|T| " fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)       ml::logLeveledImpl(ml::LogLevel::Debug, "|D| " fmt, ##__VA_ARGS__)
#define LOG_INFORMATION(fmt, ...) ml::logLeveledImpl(ml::LogLevel::Information, "|I| " fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)     ml::logLeveledImpl(ml::LogLevel::Warning, "|W| " fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)       ml::logLeveledImpl(ml::LogLevel::Error, "|E| " fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)    ml::logLeveledImpl(ml::LogLevel::Critical, "|C| " fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)       ml::logLeveledImpl(ml::LogLevel::Fatal, "|F| " fmt, ##__VA_ARGS__)
#define LOG_FATAL_V(fmt, args)    ml::logLeveledImpl(ml::LogLevel::Fatal, "|F| " fmt, args)
#else
#define LOG_LINE(fmt, ...)
#define LOG_VERBOSE(fmt, ...)
#define LOG_TRACE(fmt, ...)
#define LOG_DEBUG(fmt, ...)
#define LOG_INFORMATION(fmt, ...)
#define LOG_WARNING(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_CRITICAL(fmt, ...)
#define LOG_FATAL(fmt, ...)
#define LOG_FATAL_V(fmt, args)
#endif
