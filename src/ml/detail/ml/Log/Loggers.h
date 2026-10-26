#pragma once

#include <memory>
#include <ml/IO/ScopedFileHandle.h>
#include <ml/Network/Socket/TcpSocket.h>
#include <string_view>

namespace ml {

/**
 * Prints a message to the debug console using svcOutputDebugString
 * @param message The message to print
 * @param messageSize The size of the message
 */
void svcPrint(const char* message, size_t messageSize);

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
 * Sends logs over a TCP connection
 */
class TcpLogger {
public:
    TcpLogger() = default;

    bool connect(const char* ip, int port);
    void writeLine(std::string_view line);

private:
    std::unique_ptr<TcpSocket> mSocket;
};

}
