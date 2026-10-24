#include <ml/Network/NNErrorMapper.h>

#include <ml/Util/Logger.h>
#include <nn/socket.hpp>

namespace ml {

Result<NetError> NNErrorMapper::MapLastError(NetError fallback) {
    int errorCode = nn::socket::GetLastErrno();
    nn::socket::Errno socketErrno = static_cast<nn::socket::Errno>(errorCode);

    NetError netError = fallback;

    if (socketErrno == nn::socket::Errno::EConnRefused) {
        netError = NetError::ConnectionRefused;
    } else if (socketErrno == nn::socket::Errno::EMsgSize) {
        netError = NetError::MessageTooLarge;
    } else if (socketErrno == nn::socket::Errno::EConnReset || socketErrno == nn::socket::Errno::EConnResetPeer) {
        netError = NetError::HostUnreachable;
    } else if (socketErrno == nn::socket::Errno::ETimedOut) {
        netError = NetError::TimeOut;
    } else if (socketErrno == nn::socket::Errno::EBadF) {
        netError = NetError::BadFileDescriptor;
    } else if (socketErrno == nn::socket::Errno::ENoProtoOpt) {
        netError = NetError::OperationNotSupported;
    } else if (socketErrno == nn::socket::Errno::ENetUnreach) {
        netError = NetError::NetworkUnreachable;
    } else if (socketErrno == nn::socket::Errno::EWouldBlock) {
        netError = NetError::WouldBlock;
    } else if (socketErrno == nn::socket::Errno::EInval) {
        netError = NetError::InvalidArgument;
    } else if (socketErrno == nn::socket::Errno::EAddrNotAvail) {
        netError = NetError::NonAssignableAddress;
    }

    LOG_VERBOSE("NN Last Error: %d, (%s)", errorCode, NetErrorData::ToString(netError));

    return Result<NetError>::Failure(netError);
}

const char* NNErrorMapper::MapLastErrorStr(NetError fallback) {
    return NetErrorData::ToString(MapLastError(fallback).error());
}

}
