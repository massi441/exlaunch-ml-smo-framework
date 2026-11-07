#pragma once

#include <ArduinoJson.hpp>
#include <ml/Json/JsonNode.h>
#include <span>

namespace ml {

template <typename T>
class ModStorageArray {
public:
    ModStorageArray() = default;

    explicit ModStorageArray(JsonNode node) {
        mArray = node.as<ArduinoJson::JsonArray>();
    }

    // TODO: Key support
    // explicit ModStorageArray(const char* key) {
    //
    // }

    void copyTo(std::span<T> outBuffer) {
        for (int i = 0; i < mArray.size() && i < outBuffer.size(); i++) {
            outBuffer[i] = mArray[i].as<T>();
        }
    }

    size_t size() const {
        return mArray.size();
    }

    T get(size_t index) const {
        return mArray[index].as<T>();
    }

    T operator[](size_t index) const {
        return mArray[index].as<T>();
    }

    ArduinoJson::JsonArray::iterator begin() {
        return mArray.begin();
    }

    ArduinoJson::JsonArray::iterator end() {
        return mArray.end();
    }

    ArduinoJson::JsonArray::iterator begin() const {
        return mArray.begin();
    }

    ArduinoJson::JsonArray::iterator end() const {
        return mArray.end();
    }

private:
    ArduinoJson::JsonArray mArray;
};

}
