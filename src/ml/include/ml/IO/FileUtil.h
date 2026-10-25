#pragma once

#include <ml/Core/Container/Array.h>
#include <ml/Core/Util/Types.h>
#include <ml/Export.h>
#include <nn/fs/fs_types.h>
#include <string>

namespace nn::fs {
struct FileHandle;
}

namespace ml {

enum class FileOpenMode {
    Read = 1 << 0,
    Write = 1 << 1,
    Append = 1 << 2,

    ReadWrite = Read | Write,
    WriteAppend = Write | Append
};

/**
 * Attempts to open a file and creates it if it doesn't exist
 * @param fileHandle A pointer to the file handle
 * @param filePath The path to the file
 * @param openMode The open mode
 * @return true if the file was opened OR created successfully, false otherwise
 */
ML_EXPORT bool openOrCreateFile(nn::fs::FileHandle* fileHandle, const char* filePath, ml::FileOpenMode openMode);

/**
 * Reads a file into a given byte buffer
 * @param outBuffer The buffer to read the file into
 * @param filePath The path of the file
 * @param startOffset The offset in the file to start reading at
 * @param readSize The amount of bytes to read
 * @return true if the file was read, false otherwise
 */
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

/**
 * Checks if a given path exists, whether it is a directory or a file
 */
ML_EXPORT bool isExistPath(const char* filePath);
ML_EXPORT bool isExistFile(const char* filePath);
ML_EXPORT bool isExistDir(const char* filePath);

/**
 * Clears the contents of a file by setting its size to 0
 * @param fileHandle The file handle
 * @return true if the operation was successful, false otherwise
 */
ML_EXPORT bool clearFile(nn::fs::FileHandle fileHandle);

/**
 * Writes a buffer to a file in Append mode
 * @param fileHandle The file handle
 * @param offset The offset to start writing from
 * @param buffer The buffer holding the data to append to the file
 * @param bufferSize The size of the buffer
 * @return true if the operation was successful, false otherwise
 */
ML_EXPORT bool appendFile(nn::fs::FileHandle fileHandle, uint64_t offset, const void* buffer, size_t bufferSize);

/**
 * Gets the base path where all custom mod files are stored
 */
ML_EXPORT const char* getSdMountPath();

/**
 * Creates a path for a file located in the sd:/ directory with the given file name
 */
ML_EXPORT std::string makeSdPath(const char* fileName);

/**
 * Checks if the code is currently running on an emulator
 */
ML_EXPORT bool isEmulator();

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
