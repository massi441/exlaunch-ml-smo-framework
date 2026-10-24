#pragma once

#include <ml/Core/Container/Array.h>
#include <ml/Core/Util/Types.h>
#include <ml/Export.h>
#include <string>

namespace nn::fs {
struct FileHandle;
}

namespace ml {

enum class FileOpenMode {
    Read = 1 << 0,
    Write = 1 << 1,
    Append = 1 << 2,

    ReadWrite = Read | Write
};

/**
 * Gets the base path where all custom mod files are stored
 */
ML_EXPORT const char* getSdMountPath();

/**
 * Creates a path for a file located in the sd:/ directory with the given file name
 */
ML_EXPORT std::string makeSdPath(const char* fileName);

/**
 * Attempts to open a file and creates it if it doesn't exist
 * @param fileHandle A pointer to the file handle
 * @param filePath The path to the file
 * @param openMode The open mode
 * @return true if the file was opened OR created successfully, false otherwise
 */
ML_EXPORT bool openOrCreateFile(nn::fs::FileHandle* fileHandle, const char* filePath, ml::FileOpenMode openMode);

/**
 * Checks if a given path exists, whether it is a directory or a file
 */
ML_EXPORT bool isExistPath(const char* filePath);

ML_EXPORT bool isExistFile(const char* filePath);
ML_EXPORT bool isExistDir(const char* filePath);

ML_EXPORT bool readFile(ml::Array<byte>* outBuffer, const char* filePath, uint64_t startOffset = 0, int64_t readSize = -1);

/**
 * Replaces an open file's contents with the given data
 * @return true if all the data was written and flushed, false otherwise
 */
ML_EXPORT bool writeFile(nn::fs::FileHandle fileHandle, const void* data, size_t size);

/**
 * Replaces a file's contents with the given data, creating the file if it doesn't exist
 * @return true if all the data was written and flushed, false otherwise
 */
ML_EXPORT bool writeFile(const char* filePath, const void* data, size_t size);

inline bool openOrCreateFile(nn::fs::FileHandle* fileHandle, const std::string& filePath, ml::FileOpenMode openMode) {
    return ml::openOrCreateFile(fileHandle, filePath.c_str(), openMode);
}

inline bool isExistPath(const std::string& filePath) {
    return ml::isExistPath(filePath.c_str());
}

inline bool isExistFile(const std::string& filePath) {
    return ml::isExistFile(filePath.c_str());
}

inline bool isExistDir(const std::string& filePath) {
    return ml::isExistDir(filePath.c_str());
}

inline bool readFile(ml::Array<byte>* outBuffer, const std::string& filePath, uint64_t startOffset, int64_t readSize) {
    return ml::readFile(outBuffer, filePath.c_str(), startOffset, readSize);
}

inline bool readFile(ml::Array<byte>* outBuffer, const std::string& filePath) {
    return ml::readFile(outBuffer, filePath.c_str());
}

inline bool writeFile(const std::string& filePath, const void* data, size_t size) {
    return ml::writeFile(filePath.c_str(), data, size);
}

}
