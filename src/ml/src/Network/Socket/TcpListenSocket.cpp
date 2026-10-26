#include <ml/Network/Socket/TcpListenSocket.h>

#include <ml/Log/Log.h>
#include <ml/Network/NNErrorMapper.h>
#include <ml/Network/SocketUtil.h>
#include <nn/socket.hpp>

namespace ml {

TcpListenSocket::TcpListenSocket(int socketHandle) : Socket(socketHandle) {

}

Result<NetError> TcpListenSocket::bind(const char* address, int port) const {
    sockaddr_in bindAddr;

    Result<NetError> fillResult = ml::fillIpv4Addr(&bindAddr, address, port);
    if (fillResult.isFailed()) {
        return fillResult;
    }

    int bindResult = nn::socket::Bind(this->getHandle(), reinterpret_cast<sockaddr*>(&bindAddr), sizeof(sockaddr_in));
    if (bindResult == SOCKET_ERROR) {
        return NNErrorMapper::MapLastError(NetError::BindFailed);
    }

    LOG_DEBUG("Bound TCP listener on %s:%d", address, port);

    return Result<NetError>::Success();
}

Result<NetError> TcpListenSocket::listen(int backlog) const {
    int listenResult = nn::socket::Listen(this->getHandle(), backlog);

    if (listenResult == SOCKET_ERROR) {
        return NNErrorMapper::MapLastError(NetError::ListenFailed);
    }

    return Result<NetError>::Success();
}

ReturnResult<std::unique_ptr<TcpSocket>, NetError> TcpListenSocket::accept() const {
    int socketFd = nn::socket::Accept(this->getHandle(), nullptr, nullptr);

    if (socketFd == INVALID_SOCKET) {
        return NNErrorMapper::MapLastError<std::unique_ptr<TcpSocket>>();
    }

    std::unique_ptr<TcpSocket> socket = std::make_unique<TcpSocket>(socketFd);

    LOG_TRACE("Accepted TCP socket from listener");

    return ReturnResult<std::unique_ptr<TcpSocket>, NetError>::Success(std::move(socket));
}

}
