#include <ml/Memory/DynamicSceneHeapHook.h>

#include <exl/hook/trampoline.hpp>
#include <heap/seadExpHeap.h>
#include <ml/Core/Memory/MemorySize.h>
#include <ml/Memory/HeapUtil.h>
#include <Scene/StageScene.h>

namespace {

constexpr size_t HeapSize = ml::MemorySize::MegaBytes(1);
sead::ExpHeap* sHeap = nullptr;

HOOK_DEFINE_TRAMPOLINE(SceneInitHook) {
    static void Callback(StageScene* thisPtr, const al::SceneInitInfo& info) {
        sHeap = sead::ExpHeap::create(HeapSize, "SceneDynamicHeap", ml::findSceneHeap()); // should probably add a way to clean up later on

        Orig(thisPtr, info);
    }
};

}

sead::ExpHeap* DynamicSceneHeapHook::GetHeap() {
    return sHeap;
}

void DynamicSceneHeapHook::Install() {
    SceneInitHook::InstallAtSymbol("_ZN10StageScene4initERKN2al13SceneInitInfoE");
}
