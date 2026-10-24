#include <ml/Mod/ModRuntime.h>

#include <exl/hook/nx64/impl.hpp>
#include <exl/nx/kernel/virtmem.h>
#include <exl/patch/patcher_impl.hpp>
#include <exl/util/sys/cur_proc_handle.hpp>
#include <exl/util/sys/mem_layout.hpp>
#include <mallow/mallow.hpp>
#include <ml/Hook/FactoryHook.h>

namespace ml {

static void initLibs();
static void installHooks();

void ModRuntime::Initialize() {
    initLibs();
    installHooks();

    nn::fs::MountSdCardForDebug("sd");

    mallow::net::initializeNetwork();

// #ifdef ENABLE_LOG --> Will implement later
    mallow::init::initLogging();
// #endif

    ml::InstallFactoryHooks();
}

void initLibs() {
    exl::util::impl::InitMemLayout();
    virtmemSetup();
    exl::patch::impl::InitPatcherImpl();
    exl::util::proc_handle::Get();
    exl::hook::nx64::Initialize();

    // This sink writes to the debug console. This is useful for emulators.
    static mallow::log::sink::DebugPrintSink debugPrintSink;
    addLogSink(&debugPrintSink);
}

void installHooks() {
    // TODO: Initialize mouse, keyboard, network
}

}


