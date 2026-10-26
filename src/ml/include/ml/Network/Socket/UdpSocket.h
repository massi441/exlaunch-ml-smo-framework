#pragma once

#include <ml/Export.h>
#include <ml/Network/Socket/Socket.h>
#include <nn/socket.hpp>

namespace ml {

/**
 * A wrapper around an OS UDP socket, bound to a given endpoint
 */
class ML_EXPORT UdpSocket : public Socket {
public:
    explicit UdpSocket(int socketHandle, sockaddr_in address);

    UdpSocket() = default;

    Result<NetError> send(const void* buffer, size_t bufferSize, int flags = 0);
    Result<NetError> receive(void* buffer, int bufferLength, int* outBytesReceived, int flags = 0);

private:
    sockaddr_in mSocketAddress;

    sockaddr* getSockAddr();
    uint32_t getAddrSize() const;
};

}
