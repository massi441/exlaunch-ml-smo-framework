#pragma once

#include <ml/Export.h>
#include <ml/Network/Socket/Socket.h>
#include <ml/Network/Socket/TcpSocket.h>

namespace ml {

class ML_EXPORT TcpListenSocket : public Socket {
public:
    explicit TcpListenSocket(int socketHandle);

    TcpListenSocket() = default;

    Result<NetError> bind(const char* address, int port) const;
    Result<NetError> listen(int backlog) const;
    ReturnResult<TcpSocket, NetError> accept() const;
};

}
