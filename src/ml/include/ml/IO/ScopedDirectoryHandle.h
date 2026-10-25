#pragma once

#include <cstdint>
#include <ml/Core/Util/Macros.h>
#include <nn/fs/fs_directories.h>

namespace ml {

/**
 * A directory handle that automatically closes itself when it goes out of scope
 */
class ScopedDirectoryHandle final {
    NO_COPY(ScopedDirectoryHandle)
    NO_HEAP_ALLOC(ScopedDirectoryHandle)
public:
    ScopedDirectoryHandle() = default;

    operator nn::fs::DirectoryHandle*() { return reinterpret_cast<nn::fs::DirectoryHandle*>(&mHandle); }
    operator nn::fs::DirectoryHandle&() { return reinterpret_cast<nn::fs::DirectoryHandle&>(mHandle); }

    ~ScopedDirectoryHandle() {
        if (mHandle != -1) {
            nn::fs::CloseDirectory(*this);
        }
    }

    int64_t get() const {
        return mHandle;
    }

    bool isValid() const {
        return mHandle != -1;
    }

private:
    int64_t mHandle = -1;
};

}
