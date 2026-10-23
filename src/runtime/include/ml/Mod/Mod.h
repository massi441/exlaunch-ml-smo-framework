#pragma once

#include <concepts>

#include <ml/Util/Logger.h>

namespace ml {

class Mod {
public:
    virtual void Initialize() {}
    virtual void InstallHooks() { }
    virtual void InstallPatches() { }
    virtual void RegisterActors() { }
    virtual void RegisterAreas() { }
    virtual void RegisterCameraPosers() {}
    virtual void RegisterPlayers() { }

    virtual ~Mod() = default;
};

template<typename T>
requires std::derived_from<T, Mod>
static void RegisterMod(const char* modName) {
    LOG_INFORMATION("Registering mod: %s", modName);

    T mod = T();

    mod.Initialize();
    mod.InstallHooks();
    mod.InstallPatches();
    mod.RegisterActors();
    mod.RegisterAreas();
    mod.RegisterCameraPosers();
    mod.RegisterPlayers();
}

}
