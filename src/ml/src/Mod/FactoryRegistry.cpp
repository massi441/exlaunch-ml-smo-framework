#include <ml/Mod/FactoryRegistry.h>

#include <ml/Hook/FactoryHook.h>

namespace ml {

// each factory is installed when an entry is first registered to it.

void FactoryRegistry::registerActor(const char* entryName, al::ActorCreatorFunction createFunc) {
    ActorFactoryHook::SafeInstall("Actor", "_ZN19ProjectActorFactoryC2Ev");
    ActorFactoryHook::RegisterEntry(ActorFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerArea(const char* entryName, al::AreaCreatorFunction createFunc) {
    AreaFactoryHook::SafeInstall("Area", "_ZN18ProjectAreaFactoryC2Ev");
    AreaFactoryHook::RegisterEntry(AreaFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerCameraPoser(const char* entryName, al::CameraPoserCreatorFunction createFunc) {
    CameraPoserFactoryHook::SafeInstall("Camera", "_ZN25ProjectCameraPoserFactoryC1Ev");
    CameraPoserFactoryHook::RegisterEntry(CameraPoserFactoryHook::FactoryEntry(entryName, createFunc));
}

void FactoryRegistry::registerPlayer(const char* entryName, PlayerCreatorFunction createFunc) {
    PlayerFactoryHook::SafeInstall("Player", "_ZN13PlayerFactoryC2Ev");
    PlayerFactoryHook::RegisterEntry(PlayerFactoryHook::FactoryEntry(entryName, createFunc));
}

}
