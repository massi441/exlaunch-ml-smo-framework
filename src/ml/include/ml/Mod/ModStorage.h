#pragma once

#include <functional>
#include <ml/Json/JsonHeapAllocator.h>
#include <ml/Mod/ModStorageConfig.h>
#include <ml/Mod/ModStorageValue.h>

namespace sead {
class ExpHeap;
}

namespace ml {
class ModStorageHolder;

/**
 * Stores mod related data in a JSON file.
 */
class ModStorage {
public:
    friend ModStorageHolder;

    template <typename T>
    T get(const char* key) {
        T value = T();
        value.deserialize(this->getJson(key));
        return value;
    }

    template <typename T>
    T getValue(const char* key, T defaultValue = T()) {
        ModPrimitiveValue<T> value = defaultValue;
        value.deserialize(this->getJson(key));
        return value;
    }

    template <typename T>
    void setValue(const char* key, T value) {
        this->set(key, ModPrimitiveValue<T>(value));
    }

    ML_EXPORT void set(const char* key, const std::function<void(ml::JsonNode json)>& serializeFunc);
    ML_EXPORT void set(const char* key, const ModStorageValue& value);

    const ModStorageConfig& getConfig() const { return mConfig; }

private:
    ArduinoJson::JsonDocument mJsonDocument;
    JsonHeapAllocator mAllocator;
    ModStorageConfig mConfig = ModStorageConfig();

    explicit ModStorage(sead::ExpHeap* sequenceHeap);

    ML_EXPORT ml::JsonNode getJson(const char* key);
    bool load();
    bool save();

    ~ModStorage();
};

}
