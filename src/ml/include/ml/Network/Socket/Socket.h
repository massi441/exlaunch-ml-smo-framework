#pragma once

#include <ml/Core/Result/Result.h>
#include <ml/Core/Util/Macros.h>
#include <ml/Export.h>
#include <ml/Network/Socket/NetError.h>

namespace ml {

/**
 * An unsafe, and pure wrapper around an OS socket Handle.
 */
class ML_EXPORT Socket {
    NO_COPY(Socket)
public:
    explicit Socket(int socketHandle);

    Socket();
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    ~Socket();

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

    int getHandle() const;

private:
    int mSocketHandle;
};

}
