#include <ml/Network/Socket/SocketFactory.h>

#include <ml/Log/LogUtil.h>
#include <ml/Network/NNErrorMapper.h>
#include <ml/Network/SocketUtil.h>

namespace ml {

ml::ReturnResult<std::unique_ptr<TcpSocket>, NetError> createTcpSocket(const char* ip, int port) {
    sockaddr_in addr = sockaddr_in();

    ml::ReturnResult<int, NetError> handleResult = ml::createIpv4Socket(&addr, ip, port, SOCK_STREAM, IPPROTO_TCP);
    if (handleResult.isFailed()) {
        return ml::ReturnResult<std::unique_ptr<TcpSocket>, NetError>::Failure(handleResult.error());
    }

    int socketHandle = handleResult.data();

    int connectResult = nn::socket::Connect(socketHandle, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in));
    if (connectResult == SOCKET_ERROR) {
        nn::socket::Close(socketHandle);
        return ml::ReturnResult<std::unique_ptr<TcpSocket>, NetError>::Failure(NNErrorMapper::MapLastError().error());
    }

    LOG_TRACE("Creating TCP connection with handle %d", socketHandle);

    std::unique_ptr<TcpSocket> tcpSocket = std::make_unique<TcpSocket>(socketHandle);

    return ml::ReturnResult<std::unique_ptr<TcpSocket>, NetError>::Success(std::move(tcpSocket));
}

ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError> createTcpListenSocket(const char* address, int port, int backLog) {
    sockaddr_in addr = sockaddr_in();

    ml::ReturnResult<int, NetError> handleResult = ml::createIpv4Socket(&addr, address, port, SOCK_STREAM, IPPROTO_TCP);
    if (handleResult.isFailed()) {
        return ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError>::Failure(handleResult.error());
    }

    std::unique_ptr<TcpListenSocket> listenSocket = std::make_unique<TcpListenSocket>(handleResult.data());

    ml::Result<NetError> bindResult = listenSocket->bind(address, port);
    if (bindResult.isFailed()) {
        return ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError>::Failure(bindResult.error());
    }

    ml::Result<NetError> listenResult = listenSocket->listen(backLog);
    if (listenResult.isFailed()) {
        return ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError>::Failure(listenResult.error());
    }

    LOG_TRACE("Creating TCP listener with handle %d", listenSocket->getHandle());

    return ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError>::Success(std::move(listenSocket));
}

ml::ReturnResult<std::unique_ptr<UdpSocket>, NetError> createUdpSocket(const char* ip, int port) {
    sockaddr_in addr = sockaddr_in();

    ml::ReturnResult<int, NetError> handleResult = ml::createIpv4Socket(&addr, ip, port, SOCK_DGRAM, IPPROTO_UDP);
    if (handleResult.isFailed()) {
        return ml::ReturnResult<std::unique_ptr<UdpSocket>, NetError>::Failure(handleResult.error());
    }

    LOG_TRACE("Creating UDP connection with handle: %d", handleResult.data());

    std::unique_ptr<UdpSocket> udpSocket = std::make_unique<UdpSocket>(handleResult.data(), addr);

    return ml::ReturnResult<std::unique_ptr<UdpSocket>, NetError>::Success(std::move(udpSocket));
}

}
