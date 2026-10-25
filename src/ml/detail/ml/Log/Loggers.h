#pragma once

#include <ml/IO/ScopedFileHandle.h>
#include <string_view>

namespace ml {

/**
 * Writes log to the console using svcOutputDebugString
 */
class DebugLogger {
public:
    DebugLogger() = default;

    void writeLine(std::string_view line); // will keep it non-static in case state is added later
};

/**
 * Writes logs to a file the SD card
 */
class FileLogger {
public:
    FileLogger() = default;

    bool open(const char* filePath);
    void writeLine(std::string_view line);

protected:
    ml::ScopedFileHandle mHandle;
    uint64_t mWriteOffset = 0;
};

}
