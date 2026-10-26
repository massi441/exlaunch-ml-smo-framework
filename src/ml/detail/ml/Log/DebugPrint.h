#pragma once

#include <cstdarg>
#include <cstddef>

namespace ml {

/**
 * Prints a message to the debug console using svcOutputDebugString
 * @param message The message to print
 * @param messageSize The size of the message
 */
void svcPrint(const char* message, size_t messageSize);

/**
 * Formats and prints a message to the debug console using svcOutputDebugString
 * The message must be under 1024 bytes long.
 * @param fmt The format of the message
 * @param ... The arguments of the format
 */
void svcPrintFmt(const char* fmt, ...);

/**
 * Formats and prints a message to the debug console using svcOutputDebugString
 * The message must be under 1024 bytes long.
 * @param fmt The format of the message
 * @param args The list of arguments of the format
 */
void svcPrintFmtV(const char* fmt, va_list args);

template <size_t N>
void svcPrint(const char (&buffer)[N]) {
    ml::svcPrint(buffer, N - 1);
}

}
