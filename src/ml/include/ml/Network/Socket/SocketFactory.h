#pragma once

#include <memory>
#include <ml/Core/Result/Result.h>
#include <ml/Export.h>
#include <ml/Network/Socket/NetError.h>
#include <ml/Network/Socket/TcpListenSocket.h>
#include <ml/Network/Socket/TcpSocket.h>
#include <ml/Network/Socket/UdpSocket.h>

namespace ml {

/**
 * Creates an Ipv4 TCP socket that connects to a host IP address and port
 */
ML_EXPORT ml::ReturnResult<std::unique_ptr<TcpSocket>, NetError> createTcpSocket(const char* ip, int port);

/**
 * Creates an Ipv4 TCP socket that listens at a given port
 */
ML_EXPORT ml::ReturnResult<std::unique_ptr<TcpListenSocket>, NetError> createTcpListenSocket(const char* address, int port, int backLog);

/**
 * Creates an Ipv4 UDP socket from a host IP address and port
 */
ML_EXPORT ml::ReturnResult<std::unique_ptr<UdpSocket>, NetError> createUdpSocket(const char* ip, int port);

}
