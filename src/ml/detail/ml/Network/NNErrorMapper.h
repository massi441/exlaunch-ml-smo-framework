#pragma once

#include <ml/Network/Socket/NetError.h>

namespace ml {

class NNErrorMapper {
public:
    static Result<NetError> MapLastError(NetError fallback = NetError::GenericFailure);
    static const char* MapLastErrorStr(NetError fallback = NetError::GenericFailure);

    /**
     * Maps the last NN socket error into a ReturnResult of the specified type
     */
    template <typename T>
    static ReturnResult<T, NetError> MapLastError(NetError fallback = NetError::GenericFailure) {
        return ReturnResult<T, NetError>::Failure(MapLastError(fallback).error());
    }

private:
    NNErrorMapper() = default;
};

}
