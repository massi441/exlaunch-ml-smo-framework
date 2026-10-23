#include <mallow/logging/debug.hpp>
#include <mallow/logging/logSinks.hpp>
#include <mallow/logging/logger.hpp>

extern "C" {
/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start[])(void) __attribute__((weak));

extern void (*__preinit_array_end[])(void) __attribute__((weak));

extern void (*__init_array_start[])(void) __attribute__((weak));

extern void (*__init_array_end[])(void) __attribute__((weak));

/* Exported by program. */
void userMain();

void __init_array(void) {
    size_t i;
    size_t count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++) {
        __preinit_array_start[i]();
    }

    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++) {
        __init_array_start[i]();
    }
}

static void* initArgs[2] = {};

void entrypointInit(void* x0, void* x1) {
    __init_array();
    initArgs[0] = x0;
    initArgs[1] = x1;
    userMain();
}

void rtldInit() {
    entrypointInit(nullptr, nullptr);
}

void print_unresolved_symbol(const char* name) {
    mallow::dbg::debugPrint("Unresolved symbol: %s\n", name);
    mallow::log::logLine("Unresolved symbol: %s", name);
}

void __cxa_atexit(void (*func)(void*), void* arg, void* dso_handle) {
    (void)func;
    (void)arg;
    (void)dso_handle;

    // we will never have a graceful exit, so this doesn't matter to us
}

}
