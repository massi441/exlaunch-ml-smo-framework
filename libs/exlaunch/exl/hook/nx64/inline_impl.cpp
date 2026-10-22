#include "impl.hpp"

#include <exl/common.hpp>
#include <array>
#include "exl/armv8.hpp"
#include "exl/util/sys/jit.hpp"

namespace exl::hook::nx64 {

/* Size of stack to reserve for the context. Adjust this along with CTX_STACK_SIZE in inline_asm.s */
static constexpr int CtxStackBaseSize = 0x100;

namespace reg = exl::armv8::reg;
namespace inst = exl::armv8::inst;

struct InlineHookEntry {
    std::array<inst::Instruction, 4> mInstructions;
    uintptr_t mCallback;
    uintptr_t mTrampolineAddr;
};

static constexpr size_t InlinePoolCount = setting::InlinePoolSize / sizeof(InlineHookEntry);

JIT_CREATE(s_InlineHookJit, setting::InlinePoolSize);
static size_t s_EntryIndex = 0;

extern "C" {
    extern char exl_inline_hook_impl;
    extern char exl_inline_float_hook_impl;
}

static uintptr_t GetImpl(bool use_float_impl) {
    return use_float_impl ? reinterpret_cast<uintptr_t>(&exl_inline_float_hook_impl) :
                          reinterpret_cast<uintptr_t>(&exl_inline_hook_impl);
}

static const InlineHookEntry* GetEntryRx() {
    return reinterpret_cast<const InlineHookEntry*>(s_InlineHookJit.GetRo());
}

static InlineHookEntry* GetEntryRw() {
    return reinterpret_cast<InlineHookEntry*>(s_InlineHookJit.GetRw());
}

void InitializeInline() {
    s_InlineHookJit.Initialize();
}

InlineHookEntry* HookInline(uintptr_t hook, uintptr_t callback, bool capture_floats) {
    /* Ensure enough space in the pool. */
    if(s_EntryIndex >= InlinePoolCount) {
        EXL_ABORT(result::HookTrampolineAllocFail);
    }

    /* Grab entry from pool. */
    InlineHookEntry* entryRw = &GetEntryRw()[s_EntryIndex];
    const InlineHookEntry* entryRx = &GetEntryRx()[s_EntryIndex];

    s_EntryIndex++;

    /* Get pointer to entry's entrypoint. */
    uintptr_t entryCb = reinterpret_cast<uintptr_t>(&entryRx->mInstructions);
    /* Hook to call into the entry's entrypoint. Assign trampoline to be used by impl. */
    entryRw->mTrampolineAddr = Hook(hook, entryCb, true);
    /* Offset of LR before SP is moved. */
    static constexpr int lrBackupOffset = int(offsetof(InlineCtx, m_Gpr.m_Lr)) - CtxStackBaseSize;
    static_assert(lrBackupOffset == -0x10, "InlineCtx is not ABI compatible.");

    /* Construct entrypoint instructions. */
    uintptr_t impl = GetImpl(capture_floats);
    entryRw->mInstructions = {
        /* Backup LR register to stack, as we are about to trash it. */
        inst::SturUnscaledImmediate(reg::LR, reg::SP, lrBackupOffset),
        /* Branch to implementation. */
        inst::BranchLink(impl - (entryCb + (1 * sizeof(armv8::InstType)))),
        /* Restore proper LR. */
        inst::LdurUnscaledImmediate(reg::LR, reg::SP, lrBackupOffset),
        /* Branch to trampoline. */
        inst::Branch(entryRw->mTrampolineAddr - (entryCb + (3 * sizeof(armv8::InstType))))
    };

    /* Assign callback to be called to be used by impl. */
    entryRw->mCallback = callback;

    /* Finally, flush caches to have RX region to be consistent. */
    s_InlineHookJit.Flush();

    return entryRw;
}

void WriteReturnAddr(InlineHookEntry* hook, uintptr_t returnAddr) {
    size_t hookId = hook - GetEntryRw();
    const InlineHookEntry* entryRx = &GetEntryRx()[hookId];

    static constexpr int returnInstIdx = 0x3;
    uintptr_t hookEntryPoint = reinterpret_cast<uintptr_t>(&entryRx->mInstructions);
    uintptr_t returnInstAddress = hookEntryPoint + returnInstIdx * sizeof(armv8::InstType);

    hook->mInstructions[returnInstIdx] = inst::Branch(returnAddr - returnInstAddress);

    armDCacheFlush(&hook->mInstructions[returnInstIdx], sizeof(armv8::InstType));
    armICacheInvalidate(reinterpret_cast<void*>(returnInstAddress), sizeof(armv8::InstType));
}

void RestoreReturnAddr(InlineHookEntry* hook) {
    WriteReturnAddr(hook, hook->mTrampolineAddr);
}

uintptr_t GetTrampolineAddr(InlineHookEntry* hook) {
    return hook->mTrampolineAddr;
}

}
