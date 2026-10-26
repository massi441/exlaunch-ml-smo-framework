#pragma once

#include <ml/IO/ScopedFileHandle.h>
#include <ml/Network/Socket/TcpSocket.h>
#include <string_view>

namespace ml {

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

/**
 * Sends logs over a TCP Socket
 */
class TcpLogger {
public:
    TcpLogger() = default;

    bool connect(const char* ip, int port);
    void writeLine(std::string_view line);

private:
    TcpSocket mSocket;
};

}
