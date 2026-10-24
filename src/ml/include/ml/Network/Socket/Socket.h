#pragma once

#include <ml/Core/Result/Result.h>
#include <ml/Export.h>
#include <ml/Network/Socket/NetError.h>

namespace ml {

// TODO: Move semantics

/**
 * An unsafe, and pure wrapper around an OS socket Handle.
 */
class ML_EXPORT Socket {
protected:
    Socket(int socketHandle);

public:
    Result<NetError> setSendTimeOut(uint32_t milliseconds) const;
    Result<NetError> setReceiveTimeOut(uint32_t milliseconds) const;
    Result<NetError> setNonBlocking() const;
    Result<NetError> close();

    bool isValid() const;
    bool isClosed() const;

    /**
     * Polls without waiting
     */
    bool pollIn() const;

    ~Socket();

    int getHandle() const;

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&&) = delete;
    Socket& operator=(Socket&&) = delete;

private:
    int mSocketHandle;
};

}
