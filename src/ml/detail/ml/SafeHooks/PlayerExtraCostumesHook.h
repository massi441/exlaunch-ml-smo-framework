#pragma once

#include <ml/Hook/SafeHook.h>

class PlayerExtraCostumesHook : public ml::SafeHook<PlayerExtraCostumesHook> {
public:
    static void RequestExtraCostumes(int extraSize);

private:
    void Install() override;
};
