#pragma once

#include "exl/common.hpp"
#include "inline_impl.hpp"

namespace exl::hook::nx64 {

void Initialize();

struct InlineHookEntry;

uintptr_t Hook(uintptr_t hook, uintptr_t callback, bool do_trampoline = false);
InlineHookEntry* HookInline(uintptr_t hook, uintptr_t callback, bool capture_floats);

}