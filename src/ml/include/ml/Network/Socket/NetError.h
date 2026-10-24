#pragma once

#include <ml/Core/Result/Result.h>
#include <ml/Core/Util/Enum.h>

namespace ml {

DATA_ENUM(
    NetError,
    BadFileDescriptor,
    BindFailed,
    SocketAlreadyClosed,
    ConnectionRefused,
    GenericFailure,
    HostUnreachable,
    InvalidAddress,
    InvalidArgument,
    ListenFailed,
    MessageTooLarge,
    MessageTooSmall,
    NetworkUnreachable,
    NonAssignableAddress,
    TimeOut,
    OperationNotSupported,
    WouldBlock,
);

inline const char* ResultErrorToString(ml::Result<NetError> result) {
    return NetErrorData::ToString(result.error());
}

}
