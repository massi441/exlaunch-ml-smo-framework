#include <ml/SafeHooks/PlayerExtraCostumesHook.h>

#include <Player/PlayerAnimator.h>
#include <Player/PlayerModelHolder.h>
#include <exl/hook/inline.hpp>
#include <ml/Core/Util/MathHelpers.h>
#include <ml/Log/Log.h>

namespace {

int sExtraCostumesCount = 0;

HOOK_DEFINE_INLINE(PlayerModelHolderSizeHook) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        LOG_TRACE("Runtime: Increasing player holder size by %d", sExtraCostumesCount);

        ctx->W[1] += sExtraCostumesCount;
        sExtraCostumesCount = 0;

    }
};

// for storing the PlayerAnimator 'this' pointer in X9
HOOK_DEFINE_INLINE(PlayerAnimatorForceCapOnHook1) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        ctx->X[9] = ctx->X[0];
    }
};

// for storing the name of the current model in X1
// otherwise the "Normal" model actor is used for forcing cappy to come back
HOOK_DEFINE_INLINE(PlayerAnimatorForceCapOnHook2) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        PlayerAnimator* animator = reinterpret_cast<PlayerAnimator*>(ctx->X[9]);

        PlayerModelHolder* modelHolder = animator->mModelHolder;
        if (modelHolder == nullptr) {
            return;
        }

        PlayerModelHolder::Entry* currentModel = modelHolder->getCurrentEntry();
        if (currentModel == nullptr) {
            return;
        }

        const char* modelActorName = currentModel->name.cstr();

        ctx->X[1] = reinterpret_cast<u64>(modelActorName);
    }
};

}

void PlayerExtraCostumesHook::RequestExtraCostumes(int extraSize) {
    sExtraCostumesCount += mathi::max(0, extraSize);
}

void PlayerExtraCostumesHook::Install() {
    PlayerModelHolderSizeHook::InstallAtOffset(0x41b48c);
    PlayerAnimatorForceCapOnHook1::InstallAtOffset(0x42b570);
    PlayerAnimatorForceCapOnHook2::InstallAtOffset(0x42b580);
}
