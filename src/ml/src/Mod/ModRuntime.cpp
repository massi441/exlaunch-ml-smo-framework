#include <ml/Mod/ModRuntime.h>

#include <exl/hook/nx64/impl.hpp>
#include <exl/nx/kernel/virtmem.h>
#include <exl/patch/patcher_impl.hpp>
#include <exl/util/sys/cur_proc_handle.hpp>
#include <exl/util/sys/mem_layout.hpp>
#include <ml/Hook/FactoryHook.h>
#include <ml/Input/MouseKeyboardHook.h>
#include <ml/Log/ModLogger.h>
#include <nn/fs/fs_mount.h>

namespace ml {

static void initLibs();
static void installHooks();

void ModRuntime::Initialize() {
    initLibs();
    installHooks();

    nn::fs::MountSdCardForDebug("sd");

    ml::ModLogger::Initialize(); // must be initialized after the sd card is mounted for the file logger to work

    // TODO: Init network

    ml::InstallFactoryHooks();
}

void initLibs() {
    exl::util::impl::InitMemLayout();
    virtmemSetup();
    exl::patch::impl::InitPatcherImpl();
    exl::util::proc_handle::Get();
    exl::hook::nx64::Initialize();
}

void installHooks() {
    MouseKeyboardHook::Install();
}

}

// Symbol that exlaunch needs, we could add logging before aborting later on
namespace exl::diag {
void WEAK NORETURN NOINLINE AbortImpl(const AbortCtx& ctx) {
    svcBreak(ctx.isAssertion ? BreakReason_Assert : BreakReason_Panic, ctx.value, 0);

    UNREACHABLE;
}

}

