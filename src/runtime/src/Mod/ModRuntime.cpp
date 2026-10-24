#include <ml/Mod/ModRuntime.h>

#include <exl/hook/nx64/impl.hpp>
#include <exl/nx/kernel/virtmem.h>
#include <exl/patch/patcher_impl.hpp>
#include <exl/util/modules.hpp>
#include <exl/util/sys/cur_proc_handle.hpp>
#include <exl/util/sys/mem_layout.hpp>
#include <mallow/mallow.hpp>
#include <ml/Hook/FactoryHook.h>

namespace ml {

static void initLibs();

void ModRuntime::Initialize() {
    initLibs();

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

    using namespace exl::util;
    if (mem_layout::s_SelfModuleIdx != mem_layout::s_RtldModuleIdx) {
        // we are not rtld!

        mallow::exception::installHandlerAsSubsdk();

        // this allows atmosphere to detect symbols in our module!
        // this is only okay when we aren't rtld, as we would be overwriting the exception handler's
        // route otherwise.
        // see link for how atmosphere detects symbols used for crash reports:
        // https://github.com/Atmosphere-NX/Atmosphere/blob/c8c76bf8f8f6f9587de5d8ac1bd7090635353e9b/stratosphere/creport/source/creport_modules.cpp#L297-L335
        {
            // TODO: Make per module
            exl::util::RwPages startPage(exl::util::modules::GetSelfStart(), 0x4);
            reinterpret_cast<u32*>(startPage.GetRw())[0] = 0;
        }
    }
}

// definitions needed at runtime go here
extern "C" {

void print_unresolved_symbol(const char* name) {
    mallow::log::logLine("Unresolved symbol: %s", name);
    mallow::dbg::debugPrint("Unresolved symbol: %s\n", name);
}

}

}


