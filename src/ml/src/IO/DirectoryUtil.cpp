#include <ml/IO/DirectoryUtil.h>

#include <ml/Core/Container/Array.h>
#include <ml/IO/DirectoryEntry.h>
#include <ml/IO/ScopedDirectoryHandle.h>
#include <ml/Log/Log.h>

namespace ml {

void forEachDirectoryEntry(const char* directoryPath, DirectoryAction action) {
    ml::ScopedDirectoryHandle handle;

    nn::Result openResult = nn::fs::OpenDirectory(handle, directoryPath, nn::fs::OpenDirectoryMode_All);
    if (openResult.IsFailure()) {
        LOG_ERROR("Failed to open directory: %s, error: %d", directoryPath, openResult.GetDescription());
        return;
    }

    int64_t entryCount = 0;

    nn::Result countResult = nn::fs::GetDirectoryEntryCount(&entryCount, handle);
    if (countResult.IsFailure()) {
        LOG_ERROR("Failed to get directory entry count");
        return;
    }

    Array<nn::fs::DirectoryEntry> entries = ml::Array<nn::fs::DirectoryEntry>(entryCount);

    nn::Result readResult = nn::fs::ReadDirectory(&entryCount, entries.data(), handle, entries.size());
    if (readResult.IsFailure()) {
        LOG_ERROR("Failed to read directory");
        return;
    }

    for (nn::fs::DirectoryEntry& it : entries) {
        ml::DirectoryEntry entry = ml::DirectoryEntry(&it, directoryPath);
        std::invoke(action, entry);
    }
}

}
