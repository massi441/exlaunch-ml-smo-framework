#pragma once

#include <ml/Core/String/StringUtil.h>
#include <nn/fs/fs_types.h>
#include <string>

namespace ml {

class DirectoryEntry {
public:
    explicit DirectoryEntry(const nn::fs::DirectoryEntry* entry, const char* parentPath) {
        mEntry = entry;
        mParentPath = parentPath;
    }

    // API ideas:
    // rename(const char* newName)
    // remove()
    // ...

    const char* getName() const {
        return mEntry->mName;
    }

    int64_t getSize() const {
        return mEntry->mFileSize;
    }

    bool isFile() const {
        return mEntry->mType == nn::fs::DirectoryEntryType_File;
    }

    bool isDirectory() const {
        return mEntry->mType == nn::fs::DirectoryEntryType_Directory;
    }

    std::string getFullPath() const {
        return ml::concatString(mParentPath, this->getName());
    }

private:
    const nn::fs::DirectoryEntry* mEntry;
    const char* mParentPath;
};

}
