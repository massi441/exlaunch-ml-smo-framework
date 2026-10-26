#include <ml/Network/Socket/Socket.h>

#include <ml/Log/Log.h>
#include <ml/Network/NNErrorMapper.h>
#include <nn/socket.hpp>

namespace ml {

Socket::Socket(int socketHandle) {
    mSocketHandle = socketHandle;
}

Socket::Socket() {
    mSocketHandle = INVALID_SOCKET;
}

Socket::Socket(Socket&& other) noexcept {
    mSocketHandle = other.mSocketHandle;
    other.mSocketHandle = INVALID_SOCKET;
}

Socket& Socket::operator=(Socket&& other) noexcept {
    if (&other == this) {
        return *this;
    }

    this->close();

    mSocketHandle = other.mSocketHandle;
    other.mSocketHandle = INVALID_SOCKET;

    return *this;
}

Result<NetError> Socket::setSendTimeOut(uint32_t milliseconds) const {
    int result = nn::socket::SetSockOpt(this->getHandle(), SOL_SOCKET, SO_SNDTIMEO, &milliseconds, sizeof(milliseconds));
    if (result == SOCKET_ERROR) {
        LOG_TRACE("SEND ERROR: %d", nn::socket::GetLastErrno());
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

Result<NetError> Socket::setReceiveTimeOut(uint32_t milliseconds) const {
    int result = nn::socket::SetSockOpt(this->getHandle(), SOL_SOCKET, SO_RCVTIMEO, &milliseconds, sizeof(milliseconds));
    if (result == SOCKET_ERROR) {
        LOG_TRACE("RECEIVE ERROR: %d", nn::socket::GetLastErrno());
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

Result<NetError> Socket::setNonBlocking() const {
    int flags = nn::socket::Fcntl(this->getHandle(), nn::socket::F_GetFl, 0);
    int result = nn::socket::Fcntl(this->getHandle(), nn::socket::F_SetFl, flags | nn::socket::O_NonBlock);
    if (result == SOCKET_ERROR) {
        return NNErrorMapper::MapLastError();
    }

    return Result<NetError>::Success();
}

Result<NetError> Socket::close() {
    if (this->isClosed()) {
        return Result<NetError>::Failure(NetError::SocketAlreadyClosed);
    }

    nn::Result closeResult = nn::socket::Close(mSocketHandle);
    if (closeResult.IsFailure()) {
        return NNErrorMapper::MapLastError();
    }

    mSocketHandle = INVALID_SOCKET;

    return Result<NetError>::Success();
}

bool Socket::isValid() const {
    return mSocketHandle != INVALID_SOCKET;
}

bool Socket::isClosed() const {
    return mSocketHandle == INVALID_SOCKET;
}

bool Socket::pollIn() const {
    pollfd pollEntry = { mSocketHandle, nn::socket::PollIn, 0 };

    int result = nn::socket::Poll(&pollEntry, 1, 0);

    return result > 0 && pollEntry.revents != 0;
}

int Socket::getHandle() const {
    return mSocketHandle;
}

Socket::~Socket() {
    this->close();
}

}
