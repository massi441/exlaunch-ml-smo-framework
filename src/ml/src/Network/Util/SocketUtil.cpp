#include <ml/Network/SocketUtil.h>

namespace ml {

ml::Result<NetError> fillIpv4Addr(sockaddr_in* outAddr, const char* address, int port) {
    outAddr->sin_family = AF_INET;
    outAddr->sin_port = nn::socket::InetHtons(port);

    int ipResult = nn::socket::InetAton(address, &outAddr->sin_addr);
    if (ipResult == 0) {
        return ml::Result<NetError>::Failure(NetError::InvalidAddress);
    }

    return ml::Result<NetError>::Success();
}

ml::ReturnResult<int, NetError> createIpv4Socket(sockaddr_in* outAddr, const char* address, int port, int type, int protocol) {
    ml::Result<NetError> addrResult = fillIpv4Addr(outAddr, address, port);
    if (addrResult.isFailed()) {
        return ml::ReturnResult<int, NetError>::Failure(addrResult.error());
    }

    int handle = nn::socket::Socket(AF_INET, type, protocol);
    if (handle == INVALID_SOCKET) {
        return ml::ReturnResult<int, NetError>::Failure(NetError::GenericFailure);
    }

    return ml::ReturnResult<int, NetError>::Success(handle);
}

}
