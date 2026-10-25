#pragma once

#include <memory>
#include <ml/IO/ScopedFileHandle.h>
#include <ml/Network/Socket/TcpSocket.h>
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
 * Writes logs to a file
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

class TcpLogger {
public:
    TcpLogger() = default;

    bool connect(const char* ip, int port);
    void writeLine(std::string_view line);

private:
    std::unique_ptr<TcpSocket> mSocket;
};

}
