#pragma once

#include <ml/Export.h>
#include <ml/Network/Socket/Socket.h>

namespace ml {

/**
 * A connected TCP socket from which data can be sent or received
 */
class ML_EXPORT TcpSocket : public Socket {
public:
    explicit TcpSocket(int socketHandle);

    TcpSocket() = default;

    Result<NetError> send(const void* buffer, size_t bufferSize, int flags = 0) const;
    Result<NetError> receive(void* buffer, int bufferLength, int* outBytesReceived, int flags = 0) const;
};

}
