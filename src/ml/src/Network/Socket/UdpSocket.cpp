#include <ml/Network/Socket/UdpSocket.h>

#include <ml/Log/Log.h>
#include <ml/Network/NNErrorMapper.h>

namespace ml {

UdpSocket::UdpSocket(int socketHandle, sockaddr_in address) : Socket(socketHandle) {
    mSocketAddress = address;
}

Result<NetError> UdpSocket::send(const void* buffer, size_t bufferSize, int flags) {
    int sendResult = nn::socket::SendTo(this->getHandle(), buffer, bufferSize, flags, this->getSockAddr(), this->getAddrSize());

    if (sendResult == SOCKET_ERROR) {
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

Result<NetError> UdpSocket::receive(void* buffer, int bufferLength, int* outBytesReceived, int flags) {
    uint32_t addressLength = this->getAddrSize();

    int bytesReceived = nn::socket::RecvFrom(this->getHandle(), buffer, bufferLength, flags, this->getSockAddr(), &addressLength);

    if (outBytesReceived) {
        *outBytesReceived = bytesReceived;
    }

    if (bytesReceived < 0) {
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

sockaddr* UdpSocket::getSockAddr() {
    return reinterpret_cast<sockaddr*>(&mSocketAddress);
}

uint32_t UdpSocket::getAddrSize() const {
    return sizeof(mSocketAddress);
}

}
