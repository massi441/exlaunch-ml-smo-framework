#include <ml/Hook/FactoryRegistry.h>

#include <ml/Hook/FactoryHook.h>

namespace ml {

void InstallFactoryHooks() {
    ActorFactoryHook::Install("_ZN19ProjectActorFactoryC2Ev");
    AreaFactoryHook::Install("_ZN18ProjectAreaFactoryC2Ev");
    CameraPoserFactoryHook::Install("_ZN25ProjectCameraPoserFactoryC1Ev");
    PlayerFactoryHook::Install("_ZN13PlayerFactoryC2Ev");
}

void FactoryRegistry::registerActor(const char* entryName, al::ActorCreatorFunction createFunc) {
    ActorFactoryHook::RegisterEntry(ActorFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerArea(const char* entryName, al::AreaCreatorFunction createFunc) {
    AreaFactoryHook::RegisterEntry(AreaFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerCameraPoser(const char* entryName, al::CameraPoserCreatorFunction createFunc) {
    CameraPoserFactoryHook::RegisterEntry(CameraPoserFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerPlayer(const char* entryName, PlayerCreatorFunction createFunc) {
    PlayerFactoryHook::RegisterEntry(PlayerFactoryHook::FactoryEntry(entryName, createFunc));
}

}
