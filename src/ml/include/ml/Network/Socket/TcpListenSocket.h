#pragma once

#include <memory>
#include <ml/Export.h>
#include <ml/Network/Socket/Socket.h>
#include <ml/Network/Socket/TcpSocket.h>
#include <nn/socket.hpp>

namespace ml {

class ML_EXPORT TcpListenSocket : public Socket {
public:
    explicit TcpListenSocket(int socketHandle);

    Result<NetError> bind(const char* address, int port) const;
    Result<NetError> listen(int backlog) const;
    ReturnResult<std::unique_ptr<TcpSocket>, NetError> accept() const;
};

}
