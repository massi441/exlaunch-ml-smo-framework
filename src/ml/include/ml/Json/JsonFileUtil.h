#pragma once

#include <ArduinoJson.hpp>
#include <ml/Core/Container/Array.h>
#include <ml/IO/FileUtil.h>
#include <ml/IO/ScopedFileHandle.h>
#include <ml/Util/Logger.h>
#include <string>

namespace ml {

/**
 * Loads a JSON file from a path into an ArduinoJson::JsonDocument
 * @return true if a JSON document is loaded, false otherwise
 */
inline bool loadJson(ArduinoJson::JsonDocument* outJsonDoc, const char* filePath) {
    LOG_TRACE("Loading json file: %s", filePath);

    ml::Array<byte> buffer;
    if (!ml::readFile(&buffer, filePath)) {
        return false;
    }

    ArduinoJson::JsonDocument document;
    ArduinoJson::DeserializationError error = ArduinoJson::deserializeJson(document, buffer.data(), buffer.size());

    if (error.code() != ArduinoJson::DeserializationError::Ok) {
        LOG_ERROR("Failed to deserialize the json document '%s', error: %s", filePath, error.c_str());
        return false;
    }

    *outJsonDoc = document;

    return true;
}

// TODO: Add json formatting option support

inline bool saveJson(const ArduinoJson::JsonVariant& json, const char* filePath) {
    LOG_INFORMATION("Saving JSON file to %s", filePath);

    ml::ScopedFileHandle fileHandle;
    if (!ml::openOrCreateFile(fileHandle, filePath, ml::FileOpenMode::Write)) {
        LOG_ERROR("Error opening file");
        return false;
    }

    if (json.isNull() || json.size() == 0) {
        LOG_DEBUG("The json was null, write will be skipped");
        return false;
    }

    ml::Array<byte> buffer = ml::Array<byte>(ArduinoJson::measureJsonPretty(json));
    ArduinoJson::serializeJsonPretty(json, buffer.data(), buffer.size());

    if (!ml::writeFile(fileHandle, buffer.data(), buffer.size())) {
        return false;
    }

    LOG_INFORMATION("Successfully wrote JSON to file: %s", filePath);

    return true;
}

inline bool loadJson(ArduinoJson::JsonDocument* outJsonDoc, const std::string& filePath) {
    return ml::loadJson(outJsonDoc, filePath.c_str());
}

inline bool saveJson(const ArduinoJson::JsonVariant& json, const std::string& filePath) {
    return ml::saveJson(json, filePath.c_str());
}

}
