#pragma once

#include <ml/Core/Result/Result.h>
#include <ml/Network/Socket/NetError.h>
#include <nn/socket.hpp>

namespace ml {

Result<NetError> fillIpv4Addr(sockaddr_in* outAddr, const char* address, int port);
ml::ReturnResult<int, NetError> createIpv4Socket(sockaddr_in* outAddr, const char* address, int port, int type, int protocol);

}
