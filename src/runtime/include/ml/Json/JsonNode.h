#pragma once

#include <ArduinoJson.hpp>

namespace ml {

/**
 * A wrapper around ArduinoJson::JsonVariant that provides utilities
 * for querying inner objects and providing default values when keys are missing.
 */
class JsonNode {
public:
    JsonNode(ArduinoJson::JsonVariant variant) {
        mVariant = variant;
    }

    template <typename T>
    JsonNode& operator=(const T& value) {
        this->set(value);
        return *this;
    }

    template <typename T>
    void set(const T& value) {
        mVariant.set(value);
    }

    template <typename T>
    T as() const {
        return mVariant.as<T>();
    }

    template <typename T>
    T asOr(const T& defaultValue = T()) {
        if (!this->is<T>()) {
            this->set<T>(defaultValue);
            return defaultValue;
        }

        return this->as<T>();
    }

    template <typename T>
    T getOr(const char* key, const T& defaultValue = T()) {
        JsonNode inner = this->operator[](key);
        return inner.asOr(defaultValue);
    }

    /**
     * Returns an inner JSON node based on the given key, ensuring the inner object is created
     * even if the key was missing. The key is always copied into the JsonDocument's pool,
     * regardless of if it is a string literal or buffered string.
     */
    JsonNode operator[](const char* key) const {
        ArduinoJson::JsonVariant inner = mVariant[key];

        if (inner.isNull()) {
            inner = mVariant[key].to<ArduinoJson::JsonVariant>();
        }

        return inner;
    }

private:
    ArduinoJson::JsonVariant mVariant;

    template <typename T>
    bool is() const {
        return mVariant.is<T>();
    }
};

}
