#include <cstddef>

/**
 * This file contains code that initializes a module after it is found by rtld.
 */

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

void entrypointInit(void* x1, void* x2) {
    __init_array();
    userMain();
}

/**
 * The function called by rtld once a module is loaded
 */
void rtldInit() {
    entrypointInit(nullptr, nullptr);
}

void __cxa_atexit(void (*func)(void*), void* arg, void* dso_handle) {
    (void)func;
    (void)arg;
    (void)dso_handle;

    // we will never have a graceful exit, so this doesn't matter to us
}

}
