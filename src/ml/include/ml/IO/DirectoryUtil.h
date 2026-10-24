#pragma once

#include <functional>
#include <ml/Export.h>

namespace ml {

class DirectoryEntry;

using DirectoryAction = std::function<void(ml::DirectoryEntry&)>;

ML_EXPORT void forEachDirectoryEntry(const char* directoryPath, DirectoryAction action);

}
