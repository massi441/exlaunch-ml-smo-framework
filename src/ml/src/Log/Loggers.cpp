#include <ml/Log/Loggers.h>

#include <exl/nx/kernel/svc.h>
#include <ml/IO/FileUtil.h>
#include <ml/Util/Abort.h>

namespace ml {

void DebugLogger::writeLine(std::string_view line) {
    svcOutputDebugString(line.data(), line.size());
}


bool FileLogger::open(const char* filePath) {
    if (!ml::openOrCreateFile(mHandle, filePath, ml::FileOpenMode::WriteAppend)) {
        return false;
    }

    if (!ml::clearFile(mHandle)) {
        ml::Abort("Failed to clear log file at %s", filePath);
    }

    return true;
}

void FileLogger::writeLine(std::string_view line) {
    if (mHandle.isValid() && ml::appendFile(mHandle, mWriteOffset, line.data(), line.size())) {
        mWriteOffset += line.size();
    }
}

}
