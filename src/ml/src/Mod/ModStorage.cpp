#include <ml/Mod/ModStorage.h>

#include <heap/seadExpHeap.h>
#include <ml/Core/String/StringUtil.h>
#include <ml/IO/FileUtil.h>
#include <ml/Json/JsonFileUtil.h>

namespace ml {

namespace {

constexpr const char* FileName = "Mod/ModStorage.json"; // TODO: Scope to current Mod

}

ModStorage::ModStorage(sead::ExpHeap* sequenceHeap) : mAllocator(sequenceHeap) {

}

ml::JsonNode ModStorage::getJson(const char* key) {
    ml::JsonNode node = mJsonDocument.as<ArduinoJson::JsonVariant>();
    return node[key];
}

void ModStorage::set(const char* key, const std::function<void(ml::JsonNode json)>& serializeFunc) {
    serializeFunc(this->getJson(key));
}

void ModStorage::set(const char* key, const ModStorageValue& value) {
    value.serialize(this->getJson(key));
}

bool ModStorage::load() {
    mJsonDocument = ArduinoJson::JsonDocument(&mAllocator);

    bool result = ml::loadJson(&mJsonDocument, ml::makeSdPath(FileName));

    mConfig = this->get<ModStorageConfig>("Config");

    return result;
}

bool ModStorage::save() {
    if (!ml::saveJson(mJsonDocument, ml::makeSdPath(FileName))) {
        LOG_ERROR("The mod storage file was not saved");
        return false;
    }

    LOG_INFORMATION("Successfully saved mod storage file");

    return true;
}

ModStorage::~ModStorage() = default;

}
