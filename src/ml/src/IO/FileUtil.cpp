#include <ml/IO/FileUtil.h>

#include <ml/Core/String/StringUtil.h>
#include <ml/Core/Util/MathHelpers.h>
#include <ml/IO/ScopedFileHandle.h>
#include <ml/Log/LogUtil.h>
#include <nn/fs/fs_directories.h>

namespace ml {

const char* getSdMountPath() {
    const char* switchPath = "sd:/atmosphere/contents/0100000000010000/";
    const char* emulatorPath = "sd:/";

    return ml::isEmulator()
        ? emulatorPath
        : switchPath;
}

bool isEmulator() {
    nn::fs::DirectoryEntryType type;
    nn::fs::GetEntryType(&type, "sd:/atmosphere/package3");
    return type != nn::fs::DirectoryEntryType_File;
}

std::string makeSdPath(const char* fileName) {
    return ml::concatString(getSdMountPath(), fileName);
}

bool openOrCreateFile(nn::fs::FileHandle* fileHandle, const char* filePath, ml::FileOpenMode openMode) {
    nn::Result openResult = nn::fs::OpenFile(fileHandle, filePath, static_cast<int>(openMode));

    if (nn::fs::ResultPathNotFound::Includes(openResult)) {
        LOG_WARNING("File '%s' not found, creating it", filePath);
        nn::Result createResult = nn::fs::CreateFile(filePath, 0);

        if (createResult.IsFailure()) {
            LOG_ERROR("Error creating file '%s'", filePath);
            return false;
        }

        openResult = nn::fs::OpenFile(fileHandle, filePath, static_cast<int>(openMode));
    }

    if (openResult.IsFailure()) {
        LOG_ERROR("Error, failed to open file '%s'", filePath);
        return false;
    }

    return true;
}

bool isExistPath(const char* filePath) {
    nn::fs::DirectoryEntryType type;
    nn::Result result = nn::fs::GetEntryType(&type, filePath);

    return result.IsSuccess();
}

bool isExistDir(const char* filePath) {
    nn::fs::DirectoryEntryType type;
    nn::Result result = nn::fs::GetEntryType(&type, filePath);

    return result.IsSuccess() && type == nn::fs::DirectoryEntryType_Directory;
}

bool clearFile(nn::fs::FileHandle fileHandle) {
    return nn::fs::SetFileSize(fileHandle, 0).IsSuccess();
}

bool appendFile(nn::fs::FileHandle fileHandle, uint64_t offset, const void* buffer, size_t bufferSize) {
    return nn::fs::WriteFile(fileHandle, offset, buffer, bufferSize, nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush)).IsSuccess();
}

bool isExistFile(const char* filePath) {
    nn::fs::DirectoryEntryType type;
    nn::Result result = nn::fs::GetEntryType(&type, filePath);

    return result.IsSuccess() && type == nn::fs::DirectoryEntryType_File;
}

bool readFile(ml::Array<byte>* outBuffer, const char* filePath, uint64_t startOffset, int64_t readSize) {
    ml::ScopedFileHandle fileHandle;

    if (!ml::openOrCreateFile(fileHandle, filePath, ml::FileOpenMode::Read)) {
        LOG_ERROR("Failed to load file");
        return false;
    }

    long fileSize = 0;
    nn::Result sizeResult = nn::fs::GetFileSize(&fileSize, fileHandle);

    if (sizeResult.IsFailure()) {
        LOG_ERROR("Error, failed to get file size");
        return false;
    }

    if (fileSize == 0) {
        LOG_WARNING("Note: File %s is empty", filePath);
        return true;
    }

    if (startOffset >= fileSize) {
        LOG_ERROR("Offset %llu is too large for file size: %ld", startOffset, fileSize);
        return false;
    }

    // use maximum size if the read size is not provided by the consumer, or else clamp the consumer's read size to the maximum size
    uint64_t maxReadSize = fileSize - startOffset;
    uint64_t bufferSize = readSize <= 0 ? maxReadSize : mathi::min(readSize, maxReadSize);

    *outBuffer = ml::Array<byte>(bufferSize);

    nn::Result fileResult = nn::fs::ReadFile(fileHandle, startOffset, outBuffer->data(), outBuffer->size());

    if (fileResult.IsFailure()) {
        LOG_TRACE("Error, failed to read file: '%s'", filePath);
        return false;
    }

    return true;
}

bool writeFile(nn::fs::FileHandle fileHandle, const void* data, size_t size) {
    nn::Result sizeResult = nn::fs::SetFileSize(fileHandle, size); // resizing ensures bytes remaining from larger previous files are dropped
    if (sizeResult.IsFailure()) {
        LOG_ERROR("Failed to set the file size");
        return false;
    }

    int64_t startPos = 0;
    nn::fs::WriteOption writeOption = nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag::WriteOptionFlag_Flush);

    nn::Result writeResult = nn::fs::WriteFile(fileHandle, startPos, data, size, writeOption);
    if (writeResult.IsFailure()) {
        LOG_ERROR("Failed to write file, error: %d", writeResult.GetDescription());
        return false;
    }

    return true;
}

bool writeFile(const char* filePath, const void* data, size_t size) {
    ml::ScopedFileHandle fileHandle;
    if (!ml::openOrCreateFile(fileHandle, filePath, ml::FileOpenMode::Write)) {
        LOG_ERROR("Error opening file '%s'", filePath);
        return false;
    }

    return ml::writeFile(fileHandle, data, size);
}

}
