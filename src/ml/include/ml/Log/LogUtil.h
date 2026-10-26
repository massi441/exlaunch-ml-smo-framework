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
#define LOG_LINE(fmt, ...)        ml::logLine(fmt, ##__VA_ARGS__)
#define LOG_VERBOSE(fmt, ...)     ml::logLeveled(ml::LogLevel::Verbose, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)       ml::logLeveled(ml::LogLevel::Trace, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)       ml::logLeveled(ml::LogLevel::Debug, fmt, ##__VA_ARGS__)
#define LOG_INFORMATION(fmt, ...) ml::logLeveled(ml::LogLevel::Information, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)     ml::logLeveled(ml::LogLevel::Warning, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)       ml::logLeveled(ml::LogLevel::Error, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)    ml::logLeveled(ml::LogLevel::Critical, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)       ml::logLeveled(ml::LogLevel::Fatal, fmt, ##__VA_ARGS__)
#define LOG_FATAL_V(fmt, args)    ml::logLeveledV(ml::LogLevel::Fatal, fmt, args)
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
