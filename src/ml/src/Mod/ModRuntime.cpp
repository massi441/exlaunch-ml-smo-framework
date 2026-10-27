#include <ml/Mod/ModRuntime.h>

#include <exl/hook/nx64/impl.hpp>
#include <exl/nx/kernel/virtmem.h>
#include <exl/patch/patcher_impl.hpp>
#include <exl/util/sys/cur_proc_handle.hpp>
#include <exl/util/sys/mem_layout.hpp>
#include <ml/Hook/FactoryHook.h>
#include <ml/Input/MouseKeyboardHook.h>
#include <ml/Log/DebugPrint.h>
#include <ml/Log/ModLogger.h>
#include <ml/Memory/DynamicSceneHeapHook.h>
#include <ml/Network/Network.h>
#include <nn/fs/fs_mount.h>

namespace ml {

static void initLibs();
static void installHooks();

void ModRuntime::Initialize() {
    initLibs();
    installHooks();

    nn::fs::MountSdCardForDebug("sd");

    ml::ModLogger::Instance()->initializeFile();

    ml::Network::Initialize();

    ml::ModLogger::Instance()->initializeNetwork();
}

void initLibs() {
    exl::util::impl::InitMemLayout();
    virtmemSetup();
    exl::patch::impl::InitPatcherImpl();
    exl::util::proc_handle::Get();
    exl::hook::nx64::Initialize();
}

void installHooks() {
    // could probably make the factory hooks configurable at install time, maybe later
    // probably should use offsets depending on the version instead of symbols
    ActorFactoryHook::Install("_ZN19ProjectActorFactoryC2Ev");
    AreaFactoryHook::Install("_ZN18ProjectAreaFactoryC2Ev");
    CameraPoserFactoryHook::Install("_ZN25ProjectCameraPoserFactoryC1Ev");
    PlayerFactoryHook::Install("_ZN13PlayerFactoryC2Ev");

    MouseKeyboardHook::Install();
    DynamicSceneHeapHook::Install();
}

}

// Symbol that exlaunch needs, we could add logging before aborting later on
namespace exl::diag {
void WEAK NORETURN NOINLINE AbortImpl(const AbortCtx& ctx) {
    ml::svcPrint("EXL ABORT");

    if (ctx.format) {
        ml::svcPrintFmtV(ctx.format, ctx.args);
    }

    svcBreak(ctx.isAssertion ? BreakReason_Assert : BreakReason_Panic, ctx.value, 0);

    UNREACHABLE;
}

}

