#pragma once

#include <ml/Mod/ModRuntime.h>
#include <ml/Mod/ModStorage.h>

namespace sead {
class ExpHeap;
}

namespace ml {

template <typename T>
T getModStorage(const char* key) {
    return ml::ModRuntime::GetModStorage()->get<T>(key);
}

template <typename T>
T getModStorageValue(const char* key, T defaultValue = T()) {
    return ml::ModRuntime::GetModStorage()->getValue<T>(key, defaultValue);
}

inline void setModStorage(const char* key, const ModStorageValue& value) {
    ml::ModRuntime::GetModStorage()->set(key, value);
}

template <typename T>
void setModStorageValue(const char* key, T value) {
    ml::ModRuntime::GetModStorage()->setValue<T>(key, value);
}

}
