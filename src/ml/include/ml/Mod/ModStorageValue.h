#pragma once

#include <ml/Json/JsonNode.h>

namespace ml {

/**
 * An interface for a type that can be serialized and deserialized to the Mod's storage file.
 */
class ModStorageValue {
public:
    virtual void serialize(ml::JsonNode json) const = 0;
    virtual void deserialize(ml::JsonNode json) = 0;
};

/**
 * Reads and writes a primitive value to the current mod's storage file
 * @tparam T The type of value to read and write
 */
template <typename T>
class ModPrimitiveValue : public ModStorageValue {
public:
    ModPrimitiveValue() = default;

    ModPrimitiveValue(T defaultValue) {
        mValue = defaultValue;
    }

    void serialize(ml::JsonNode json) const override {
        json.set<T>(mValue);
    }

    void deserialize(ml::JsonNode json) override {
        if (!json.is<T>()) {
            json.set<T>(mValue);
            return;
        }

        mValue = json.as<T>();
    }

    T get() const {
        return mValue;
    }

    void set(T value) {
        mValue = value;
    }

    operator T() const {
        return mValue;
    }

private:
    T mValue = T();
};

}
