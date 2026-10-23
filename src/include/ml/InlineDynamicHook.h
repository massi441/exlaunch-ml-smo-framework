#pragma once

#include <exl/hook/base.hpp>
#include <ml/Hook/HookUtil.h>
#include <ml/Util/Abort.h>

#define HOOK_DEFINE_INLINE_DYNAMIC(Name) struct Name : public ml::InlineDynamicHook<Name>\

namespace ml {

/**
 * An opaque branch target for a dynamic inline hook's return address.
 */
struct InlineBranch {
private:
    explicit InlineBranch(uint64_t branch) {
        mBranch = branch;
    }

    uint64_t get() const { return mBranch; }
    operator uint64_t() const { return mBranch; }

    template <typename Derived>
    friend struct InlineDynamicHook;

private:
    uint64_t mBranch;
};

/**
 * An inline hook able to dynamically control where the program returns after the hook's Callback.
 * Note: This hook does not work as intended on Ryujinx, due to how cache flushes are emulated
 * @tparam Derived The type of hook, used for CRTP
 */
template <typename Derived>
struct InlineDynamicHook {
public:
    template <typename T>
    using CallbackFunc = decltype(&T::Callback);

    using Base = InlineDynamicHook;

    static void InstallAtOffset(ptrdiff_t offset) {
        ASSERT_STATIC_CALLBACK(CallbackFunc<Derived>);

        sHookedAddr = ml::getRuntimeAddress(offset);

        sHookEntry = exl::hook::HookInline(sHookedAddr, &HookFunc);
    }

    static void InstallAtPtr(uintptr_t ptr) {
        ASSERT_STATIC_CALLBACK(CallbackFunc<Derived>);

        sHookedAddr = ptr;

        sHookEntry = exl::hook::HookInline(ptr, &HookFunc);
    }

    static void InstallAtSymbol(const char* symbol) {
        ASSERT_STATIC_CALLBACK(CallbackFunc<Derived>);

        ml::AbortIf(!ml::lookUpSymbol(&sHookedAddr, symbol), "ERROR: Symbol \"%s\" does not exist", symbol);

        sHookEntry = exl::hook::HookInline(sHookedAddr, &HookFunc);
    }

protected:

    /**
     * Creates an InlineBranch to a specific runtime address
     * @param runtimeAddress The runtime address of the instruction to branch to
     */
    static InlineBranch Branch(uintptr_t runtimeAddress) {
        return InlineBranch(runtimeAddress);
    }

    /**
     * Creates an InlineBranch to an instruction at a given module offset
     * @param offset The offset of the instruction in the module (found in the disassembly)
     */
    static InlineBranch BranchOffset(ptrdiff_t offset) {
        return InlineBranch(ml::getRuntimeAddress(offset));
    }

    /**
     * Creates an InlineBranch to an instruction relative to the hooked address
     * @param hookRelativeOffset Byte offset from the hooked instruction
     */
    static InlineBranch BranchRel(ptrdiff_t hookRelativeOffset) {
        return InlineBranch(sHookedAddr + hookRelativeOffset);
    }

    /**
     * Creates an InlineBranch to the trampoline of the hooked instruction,
     * making the dynamic inline hook behave like a regular inline hook
     */
    static InlineBranch BranchOrig() {
        return InlineBranch(exl::hook::nx64::GetTrampolineAddr(sHookEntry));
    }

    /**
     * Creates an InlineBranch to one instruction past the hooked instruction,
     * essentially making the inline hook overwrite the hooked instruction
     */
    static InlineBranch BranchPastOrig() {
        return InlineBranch(sHookedAddr + sizeof(uint32_t));
    }

private:
    inline static exl::hook::nx64::InlineHookEntry* sHookEntry;
    inline static uintptr_t sHookedAddr;
    inline static uintptr_t sPrevReturnAddr = 0;

    // Potential TODO: Thread local storage?

    static void HookFunc(exl::hook::nx64::InlineCtx* ctx) {
        InlineBranch returnAddr = Derived::Callback(ctx);
        if (returnAddr != sPrevReturnAddr) {
            exl::hook::nx64::WriteReturnAddr(sHookEntry, returnAddr);
        }

        sPrevReturnAddr = returnAddr;
    }
};

}
