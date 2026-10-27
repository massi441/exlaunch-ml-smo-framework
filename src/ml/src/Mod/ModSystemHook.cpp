#include <ml/Mod/ModSystemHook.h>

#include <exl/hook/trampoline.hpp>
#include <ml/Mod/ModSystem.h>
#include <Project/Memory/MemorySystem.h>
#include <Project/Scene/SceneInitInfo.h>
#include <Scene/StageScene.h>
#include <Sequence/HakoniwaSequence.h>
#include <System/GameDataHolder.h>

namespace {

HOOK_DEFINE_TRAMPOLINE(HakoniwaSequenceCtorHook) {
    static void Callback(HakoniwaSequence* thisPtr) {
        Orig(thisPtr);

        ModSystemHook::GetSystem()->initialize();
    }
};

HOOK_DEFINE_TRAMPOLINE(HakoniwaSequenceDtorHook) {
    static void Callback(HakoniwaSequence* thisPtr) {
        ModSystemHook::GetSystem()->finalize();

        Orig(thisPtr);
    }
};

HOOK_DEFINE_TRAMPOLINE(CreateSceneHeapHook) {
    static bool Callback(al::MemorySystem* thisPtr, const char* stageName, bool isBackwards) {
        bool isResourceHeapCreated = Orig(thisPtr, stageName, isBackwards);

        ModSystemHook::GetSystem()->createSceneHeap(thisPtr->getSceneHeap());

        return isResourceHeapCreated;
    }
};

HOOK_DEFINE_TRAMPOLINE(DestroySceneHeapHook) {
    static void Callback(al::MemorySystem* thisPtr) {
        ModSystemHook::GetSystem()->destroySceneHeap();

        Orig(thisPtr);
    }
};

HOOK_DEFINE_TRAMPOLINE(SceneInitHook) {
    static void Callback(StageScene* thisPtr, const al::SceneInitInfo& info) {
        ModSystemHook::GetSystem()->onSceneInit();

        Orig(thisPtr, info);
    }
};

HOOK_DEFINE_TRAMPOLINE(GameSaveHook) {
    static void Callback(GameDataHolder* thisPtr, const char* fileName) {
        Orig(thisPtr, fileName);

        ModSystemHook::GetSystem()->onGameSave(fileName);
    }
};

}

ml::ModSystem* ModSystemHook::GetSystem() {
    static ml::ModSystem sSystem;
    return &sSystem;
}

void ModSystemHook::Install() {
    HakoniwaSequenceCtorHook::InstallAtSymbol("_ZN16HakoniwaSequenceC1EPKc");
    HakoniwaSequenceDtorHook::InstallAtSymbol("_ZN16HakoniwaSequenceD1Ev");
    CreateSceneHeapHook::InstallAtSymbol("_ZN2al12MemorySystem15createSceneHeapEPKcb");
    DestroySceneHeapHook::InstallAtSymbol("_ZN2al12MemorySystem16destroySceneHeapEv");
    SceneInitHook::InstallAtSymbol("_ZN10StageScene4initERKN2al13SceneInitInfoE");
    GameSaveHook::InstallAtSymbol("_ZN14GameDataHolder21writeToSaveDataBufferEPKc");
}
