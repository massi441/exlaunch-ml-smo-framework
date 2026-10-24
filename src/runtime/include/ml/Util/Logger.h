#pragma once

#include <cstdarg>
#include <mallow/config.hpp>
#include <mallow/logging/logger.hpp>

namespace ml {

inline void logLeveledV(const char* prefix, const char* fmt, va_list args) {
    mallow::log::log(prefix);
    mallow::log::logLine(fmt, args);
}

inline void logLeveled(const char* prefix, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ml::logLeveledV(prefix, fmt, args);
    va_end(args);
}

inline bool isLogEnabled(mallow::config::LogLevel level) {
    return mallow::config::getConfig()->logLevel <= level;
}

}

#ifdef ML_ENABLE_LOG
#define LOG_LINE(fmt, ...)                                                                    mallow::log::logLine(fmt, ##__VA_ARGS__)
#define LOG_VERBOSE(fmt, ...)     if (ml::isLogEnabled(mallow::config::LogLevel::Verbose))     ml::logLeveled("|V| ", fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)       if (ml::isLogEnabled(mallow::config::LogLevel::Trace))       ml::logLeveled("|T| ", fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)       if (ml::isLogEnabled(mallow::config::LogLevel::Debug))       ml::logLeveled("|D| ", fmt, ##__VA_ARGS__)
#define LOG_INFORMATION(fmt, ...) if (ml::isLogEnabled(mallow::config::LogLevel::Information)) ml::logLeveled("|I| ", fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)     if (ml::isLogEnabled(mallow::config::LogLevel::Warning))     ml::logLeveled("|W| ", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)       if (ml::isLogEnabled(mallow::config::LogLevel::Error))       ml::logLeveled("|E| ", fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)    if (ml::isLogEnabled(mallow::config::LogLevel::Critical))    ml::logLeveled("|C| ", fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)       if (ml::isLogEnabled(mallow::config::LogLevel::Fatal))       ml::logLeveled("|F| ", fmt, ##__VA_ARGS__)
#define LOG_FATAL_V(fmt, args)    if (ml::isLogEnabled(mallow::config::LogLevel::Fatal))       ml::logLeveledV("|F| ", fmt, args)
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
