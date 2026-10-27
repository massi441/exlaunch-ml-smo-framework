#pragma once

#include <ml/Mod/ModStorageValue.h>

namespace ml {

struct ModStorageConfig : ModStorageValue {
    bool isReloadBetweenStages;

    void serialize(ml::JsonNode json) const override {
        json["ReloadBetweenStages"] = isReloadBetweenStages;
    }

    void deserialize(ml::JsonNode json) override {
        isReloadBetweenStages = json.getOr("ReloadBetweenStages", true);
    }
};

}
