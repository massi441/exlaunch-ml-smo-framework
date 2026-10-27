#include <ml/SafeHooks/HeapSizeHook.h>

#include <exl/hook/inline.hpp>
#include <exl/hook/trampoline.hpp>
#include <heap/seadExpHeap.h>
#include <heap/seadFrameHeap.h>
#include <ml/Core/Memory/MemorySize.h>
#include <ml/Log/Log.h>

namespace {

// TODO: Abort if installed too late

constexpr size_t DESIRED_ROOT_HEAP_SIZE = ml::MemorySize::MegaBytes(6082); // around 5.94GB, complete magic number found after countless trial and error. Note: May need to shrink it as subsdk's grow in size
constexpr size_t WorldResourceHeapExtraSize = ml::MemorySize::MegaBytes(575);
constexpr size_t SceneHeapExtraSize = ml::MemorySize::MegaBytes(375);

void ExpandHeapSize() {
    nn::os::SetMemoryHeapSize(DESIRED_ROOT_HEAP_SIZE);

    LOG_INFORMATION("APPLICATION HEAP SIZE: %lluMB", DESIRED_ROOT_HEAP_SIZE / ml::MemorySize::MB);
}

HOOK_DEFINE_TRAMPOLINE(ExpHeapCreateHook) {
    static sead::ExpHeap* Callback(uint64_t size, const sead::SafeString& name, const sead::Heap* parent, int s32, const sead::Heap::HeapDirection direction, bool boolean) {
        if (name == "WorldHeapResource") {
            LOG_DEBUG("World Heap Size before: %zu", size / ml::MemorySize::MB);
            size += WorldResourceHeapExtraSize;
            LOG_DEBUG("World Heap Size after: %zu", size / ml::MemorySize::MB);
        }

        return Orig(size, name, parent, s32, direction, boolean);
    }
};

HOOK_DEFINE_TRAMPOLINE(FrameHeapCreateHook) {
    static sead::FrameHeap* Callback(uint64_t size, const sead::SafeString& name, const sead::Heap* parent, int s32, const sead::Heap::HeapDirection direction, bool boolean) {
        if (name == "SceneHeap") {
            LOG_DEBUG("Scene Size before: %zu", size / ml::MemorySize::MB);
            size += SceneHeapExtraSize;
            LOG_DEBUG("Scene Size after: %zu", size / ml::MemorySize::MB);
        }

        return Orig(size, name, parent, s32, direction, boolean);
    }
};

HOOK_DEFINE_TRAMPOLINE(HeapCtorHook) {
    static void Callback(sead::Heap* thisPtr, const sead::SafeString& name, sead::Heap* parent, void* address, uint64_t size, sead::Heap::HeapDirection direction, bool boolean) {
        if (name == "RootHeap") {
            LOG_DEBUG("Size: of root heap %zu", size / ml::MemorySize::MB);
        }

        Orig(thisPtr, name, parent, address, size, direction, boolean);
    }
};

HOOK_DEFINE_INLINE(ApplicationFunctionHeapSizeExpansionHook) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        ctx->X[8] += ml::MemorySize::MegaBytes(1000);

        LOG_DEBUG("Size of Root Heap: %lluMB", ctx->X[8] / ml::MemorySize::MB);
    }
};

}

void HeapSizeHook::Install() {
    ExpandHeapSize();

    ApplicationFunctionHeapSizeExpansionHook::InstallAtOffset(0x5157bc);
    HeapCtorHook::InstallAtSymbol("_ZN4sead4HeapC2ERKNS_14SafeStringBaseIcEEPS0_PvmNS0_13HeapDirectionEb");
    ExpHeapCreateHook::InstallAtSymbol("_ZN4sead7ExpHeap6createEmRKNS_14SafeStringBaseIcEEPNS_4HeapEiNS5_13HeapDirectionEb");
    FrameHeapCreateHook::InstallAtSymbol("_ZN4sead9FrameHeap6createEmRKNS_14SafeStringBaseIcEEPNS_4HeapEiNS5_13HeapDirectionEb");
}
