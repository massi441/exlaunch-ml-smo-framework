#pragma once

#include <ml/Export.h>

#include "Player/PlayerFactory.h"
#include "Scene/ProjectActorFactory.h"
#include "Scene/ProjectAreaFactory.h"
#include "Scene/ProjectCameraPoserFactory.h"

namespace ml {

// non-templates funcs are private, that way consumers only call the templated variants (the template variants have friend access to the factory registry)

/**
 * A registry for registering custom factories entries.
 * All its functions are private, use the free registry functions below instead.
 */
class FactoryRegistry {
private:
    ML_EXPORT static void registerActor(const char* entryName, al::ActorCreatorFunction createFunc);
    ML_EXPORT static void registerArea(const char* entryName, al::AreaCreatorFunction createFunc);
    ML_EXPORT static void registerCameraPoser(const char* entryName, al::CameraPoserCreatorFunction createFunc);
    ML_EXPORT static void registerPlayer(const char* entryName, PlayerCreatorFunction createFunc);

    template <typename T>
    static al::LiveActor* createCustomActorFunc(const char* actorName) {
        return new T(actorName);
    }

    template <typename T>
    static al::CameraPoser* createCustomCameraPoseFunc(const char* poseName) {
        return new T(poseName);
    }

    template <typename T>
    static al::AreaObj* createCustomAreaFunc(const char* areaName) {
        return new T(areaName);
    }

    template <typename T>
    static PlayerActorBase* createCustomPlayerFunc(const char* playerName) {
        return new T(playerName);
    }

    template <typename T> friend
    void RegisterFactoryActor(const char* entryName);

    template <typename T> friend
    void RegisterFactoryArea(const char* entryName);

    template <typename T> friend
    void RegisterFactoryCameraPoser(const char* entryName);

    template <typename T> friend
    void RegisterFactoryPlayer(const char* entryName);
};

/**
 * Registers a custom actor to the current actor factory hook provided by the runtime.
 * Note, the entry is rejected if its name is found in the existing factory entries
 * @tparam T The type of the custom actor
 * @param entryName The name of the entry in the factory
 */
template <typename T>
void RegisterFactoryActor(const char* entryName) {
    FactoryRegistry::registerActor(entryName, &FactoryRegistry::createCustomActorFunc<T>);
}

/**
 * Registers a custom area to the current area factory hook provided by the runtime.
 * Note, the entry is rejected if its name is found in the existing factory entries
 * @tparam T The type of the custom area
 * @param entryName The name of the entry in the factory
 */
template <typename T>
void RegisterFactoryArea(const char* entryName) {
    FactoryRegistry::registerArea(entryName, &FactoryRegistry::createCustomAreaFunc<T>);
}

/**
 * Registers a custom camera poser to the current camera poser factory hook provided by the runtime.
 * Note, the entry is rejected if its name is found in the existing factory entries
 * @tparam T The type of the custom camera poser
 * @param entryName The name of the entry in the factory
 */
template <typename T>
void RegisterFactoryCameraPoser(const char* entryName) {
    FactoryRegistry::registerCameraPoser(entryName, &FactoryRegistry::createCustomCameraPoseFunc<T>);
}

/**
 * Registers a custom player to the current player factory hook provided by the runtime.
 * Note, the entry is rejected if its name is found in the existing factory entries
 * @tparam T The type of the custom player
 * @param entryName The name of the entry in the factory
 */
template <typename T>
void RegisterFactoryPlayer(const char* entryName) {
    FactoryRegistry::registerPlayer(entryName, &FactoryRegistry::createCustomPlayerFunc<T>);
}

}
