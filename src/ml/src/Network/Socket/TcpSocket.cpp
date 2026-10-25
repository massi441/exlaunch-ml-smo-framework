#include <ml/Network/Socket/TcpSocket.h>

#include <ml/Network/NNErrorMapper.h>
#include <nn/socket.hpp>

namespace ml {

TcpSocket::TcpSocket(int socketHandle) : Socket(socketHandle) {

}

Result<NetError> TcpSocket::send(const void* buffer, size_t bufferSize, int flags) const {
    int sendResult = nn::socket::Send(this->getHandle(), buffer, bufferSize, flags);

    if (sendResult == SOCKET_ERROR) {
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

Result<NetError> TcpSocket::receive(void* buffer, int bufferLength, int* outBytesReceived, int flags) const {
    int bytesReceived = nn::socket::Recv(this->getHandle(), buffer, bufferLength, flags);

    if (outBytesReceived) {
        *outBytesReceived = bytesReceived;
    }

    if (bytesReceived == 0) {
        return Result<NetError>::Failure(NetError::HostUnreachable);
    }

    if (bytesReceived < 0) {
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

}
