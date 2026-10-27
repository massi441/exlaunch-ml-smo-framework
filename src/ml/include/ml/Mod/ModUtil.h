#pragma once

#include <ml/Export.h>
#include <ml/Mod/ModStorage.h>

namespace sead {
class ExpHeap;
}

namespace ml {

/**
 * Returns the current instance of the mod storage
 */
ML_EXPORT ModStorage* getModStorage();

/**
 * Returns the current instance of the dynamic scene heap installed by the mod runtime
 */
ML_EXPORT sead::ExpHeap* getDynamicSceneHeap();

/**
 * Returns the heap installed by the mod runtime that lives as long as the HakoniwaSequence, across scene changes
 */
ML_EXPORT sead::ExpHeap* getModSequenceHeap();

template <typename T>
T getModStorage(const char* key) {
    return getModStorage()->get<T>(key);
}

template <typename T>
T getModStorageValue(const char* key, T defaultValue = T()) {
    return getModStorage()->getValue<T>(key, defaultValue);
}

inline void setModStorage(const char* key, const ModStorageValue& value) {
    getModStorage()->set(key, value);
}

template <typename T>
void setModStorageValue(const char* key, T value) {
    getModStorage()->setValue<T>(key, value);
}


}
