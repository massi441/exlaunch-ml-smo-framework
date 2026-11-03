#include <ml/Mod/ModRuntime.h>

#include <exl/hook/nx64/impl.hpp>
#include <exl/nx/kernel/virtmem.h>
#include <exl/patch/patcher_impl.hpp>
#include <exl/util/sys/cur_proc_handle.hpp>
#include <exl/util/sys/mem_layout.hpp>
#include <ml/Hook/FactoryHook.h>
#include <ml/Hook/SafeHook.h>
#include <ml/Input/MouseKeyboardHook.h>
#include <ml/Log/ModLogger.h>
#include <ml/Mod/ModSystem.h>
#include <ml/Mod/ModSystemHook.h>
#include <ml/Network/Network.h>
#include <ml/SafeHooks/HeapSizeHook.h>
#include <ml/SafeHooks/PlayerExtraCostumesHook.h>
#include <nn/fs/fs_mount.h>

namespace ml {

static void initLibs();
static void installHooks();

void ModRuntime::Initialize() {
    if (sInitialized) {
        return;
    }

    initLibs();
    installHooks();

    nn::fs::MountSdCardForDebug("sd");

    ml::ModLogger::Instance()->initializeFile();

    ml::Network::Initialize();

    ml::ModLogger::Instance()->initializeNetwork();

    sInitialized = true;
}

void initLibs() {
    exl::util::impl::InitMemLayout();
    virtmemSetup();
    exl::patch::impl::InitPatcherImpl();
    exl::util::proc_handle::Get();
    exl::hook::nx64::Initialize();
}

// Note: Factory hooks are lazily installed as entries get added in FactoryRegistry.cpp
void installHooks() {
    MouseKeyboardHook::Install();
    ModSystemHook::Install();
}

ml::ModStorage* ModRuntime::GetModStorage() {
    return ModSystemHook::GetSystem()->getModStorage();
}

sead::ExpHeap* ModRuntime::GetModSequenceHeap() {
    return ModSystemHook::GetSystem()->getSequenceHeap();
}

sead::ExpHeap* ModRuntime::GetDynamicSceneHeap() {
    return ModSystemHook::GetSystem()->getDynamicSceneHeap();
}

void ModRuntime::RequestExtraPlayerCostumes(int extraCount) {
    ml::InstallSafeHook<PlayerExtraCostumesHook>(); // already prevent double installs

    PlayerExtraCostumesHook::RequestExtraCostumes(extraCount);
}

void ModRuntime::RequestMemoryExpansion() {
    ml::InstallSafeHook<HeapSizeHook>();
}

}
