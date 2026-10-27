#include <ml/Log/Loggers.h>

#include <ml/IO/FileUtil.h>
#include <ml/Log/Log.h>
#include <ml/Network/Socket/SocketFactory.h>
#include <ml/Util/Abort.h>

namespace ml {

bool FileLogger::open(const char* filePath) {
    if (!ml::openOrCreateFile(mHandle, filePath, ml::FileOpenMode::WriteAppend)) {
        return false;
    }

    if (!ml::clearFile(mHandle)) {
        nn::fs::CloseFile(mHandle);
        LOG_ERROR("Failed to clear log file at %s", filePath); // should probably swallow the error
    }

    return true;
}

void FileLogger::writeLine(std::string_view line) {
    if (mHandle.isValid() && ml::appendFile(mHandle, mWriteOffset, line.data(), line.size())) {
        mWriteOffset += line.size();
    }
}

bool TcpLogger::connect(const char* ip, int port) {
    ml::ReturnResult<TcpSocket, NetError> result = ml::createTcpSocket(ip, port);
    if (result.isFailed()) {
        LOG_ERROR("Failed to connect to TCP logger socket at %s: %s", ip, NetErrorData::ToString(result.error()));
        return false;
    }

    mSocket = std::move(result.data());

    return true;
}

void TcpLogger::writeLine(std::string_view line) {
    if (!mSocket.isValid()) {
        return;
    }

    // TODO: Add reconnect logic
    Result<NetError> sendResult = mSocket.send(line.data(), line.size());
    if (sendResult.isFailed()) {
        ml::Result<NetError> closeResult = mSocket.close();

        if (closeResult.isFailed()) {
            ml::Abort("Fatal Error: Failed to close TCP logger socket after failing to send log. Send error: %s, Close error: %s",
                NetErrorData::ToString(sendResult.error()),
                NetErrorData::ToString(closeResult.error())
            );
        }
    }
}

}
