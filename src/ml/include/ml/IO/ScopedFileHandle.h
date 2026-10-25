#pragma once

#include <cstdint>
#include <ml/Core/Util/Macros.h>
#include <nn/fs/fs_files.h>

namespace ml {

/**
 * A file handle that automatically closes itself when it goes out of scope
 */
class ScopedFileHandle final {
    NO_COPY(ScopedFileHandle)
    NO_HEAP_ALLOC(ScopedFileHandle)
public:
    ScopedFileHandle() = default;

    /**
     * Implicitly converts the current ScopedFileHandle to a nn::fs::FileHandle*
     * Makes it easy to pass the scoped handle to functions writing to an out nn::fs::FileHandle* parameter
     */
    operator nn::fs::FileHandle*() { return reinterpret_cast<nn::fs::FileHandle*>(&mHandle); }
    operator nn::fs::FileHandle&() { return reinterpret_cast<nn::fs::FileHandle&>(mHandle); }

    ~ScopedFileHandle() {
        if (mHandle != -1) {
            nn::fs::CloseFile(*this);
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
