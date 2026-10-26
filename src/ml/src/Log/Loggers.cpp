#include <ml/Log/Loggers.h>

#include <exl/nx/kernel/svc.h>
#include <ml/IO/FileUtil.h>
#include <ml/Log/LogUtil.h>
#include <ml/Network/Socket/SocketFactory.h>
#include <ml/Util/Abort.h>

namespace ml {

void svcPrint(const char* message, size_t messageSize) {
    svcOutputDebugString(message, messageSize);
}

bool FileLogger::open(const char* filePath) {
    if (!ml::openOrCreateFile(mHandle, filePath, ml::FileOpenMode::WriteAppend)) {
        return false;
    }

    if (!ml::clearFile(mHandle)) {
        LOG_ERROR("Failed to clear log file at %s", filePath); // should probably swallow the error
        nn::fs::CloseFile(mHandle);
    }

    return true;
}

void FileLogger::writeLine(std::string_view line) {
    if (mHandle.isValid() && ml::appendFile(mHandle, mWriteOffset, line.data(), line.size())) {
        mWriteOffset += line.size();
    }
}

bool TcpLogger::connect(const char* ip, int port) {
    mSocket = ml::createTcpSocket(ip, port).data();
    return mSocket.isValid();
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
