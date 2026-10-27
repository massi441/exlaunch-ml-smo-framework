#include <ml/CoreSMO/Player/PlayerAnimUtil.h>

#include <Player/PlayerActorBase.h>
#include <Player/PlayerAnimator.h>

namespace ml {

void startPlayerAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startAnim(animName);
}

void startPlayerAnimCommon(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startAnimCommon(animName);
}

void startPlayerAnimSpinAttack(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startAnimSpinAttack(animName);
}

void startPlayerSubAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startSubAnim(animName);
}

void startPlayerSubAnimOnlyAir(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startSubAnimOnlyAir(animName);
}

void startPlayerUpperBodyAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startUpperBodyAnim(animName);
}

void startPlayerUpperBodyAnimSubParts(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startUpperBodyAnimSubParts(animName);
}

void startPlayerUpperBodyAnimAndHeadVisKeep(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startUpperBodyAnimAndHeadVisKeep(animName);
}

void startPlayerAnimDead(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startAnimDead();
}

void startPlayerPartsAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startPartsAnim(animName);
}

void startPlayerPartsPartialAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startPartsPartialAnim(animName);
}

void startPlayerRightHandAnim(PlayerActorBase* player, const char* animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startRightHandAnim(animName);
}

void startPlayerEyeControlAnim(PlayerActorBase* player, bool value) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startEyeControlAnim(value);
}

void startPlayerPress(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startPress();
}

void startPlayerSnapShotMode(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->startSnapShotMode();
}

void endPlayerSubAnim(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->endSubAnim();
}

void endPlayerEyeControlAnim(PlayerActorBase* player, int value) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->endEyeControlAnim(value);
}

void endPlayerSnapShotMode(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->endSnapShotMode();
}

void endPlayerDemoInvalidateModelAlpha(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->endDemoInvalidateModelAlpha();
}

void updatePlayerAnimFrame(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->updateAnimFrame();
}

void updatePlayerModel(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->updateModel();
}

void updatePlayerModelAlpha(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->updateModelAlpha();
}

void updatePlayerEyeControlAnim(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->updateEyeControlAnim();
}

void clearPlayerUpperBodyAnim(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->clearUpperBodyAnim();
}

void clearPlayerInterpolation(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->clearInterpolation();
}

void clearPlayerEndEyeControlAnimDelay(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->clearEndEyeControlAnimDelay();
}

void copyPlayerAnim(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->copyAnim();
}

void copyPlayerAnimLocal(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->copyAnimLocal();
}

void applyPlayerBlendWeight(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->applyBlendWeight();
}

void forcePlayerCapOn(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->forceCapOn();
}

void forcePlayerCapOff(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->forceCapOff();
}

void overwridePlayerYoshiEatVis(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->overwrideYoshiEatVis();
}

void restartPlayerYoshiActionVis(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->restartYoshiActionVis();
}

void recordPlayerRunStartAnimRate(PlayerActorBase* player, float rate) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->recordRunStartAnimRate(rate);
}

void resetPlayerModelAlpha(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->resetModelAlpha();
}

bool isPlayerAnim(PlayerActorBase* player, const sead::SafeString& animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isAnim(animName);
}

bool isPlayerAnimEnd(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isAnimEnd();
}

bool isPlayerSubAnim(PlayerActorBase* player, const sead::SafeString& subAnimName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isSubAnim(subAnimName);
}

bool isPlayerSubAnimEnd(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isSubAnimEnd();
}

bool isPlayerUpperBodyAnimAttached(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isUpperBodyAnimAttached();
}

bool isPlayerSubAnimPlaying(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    return animator->isSubAnimPlaying();
}

float getPlayerAnimFrame(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getAnimFrame();
}

float getPlayerAnimFrameMax(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getAnimFrameMax();
}

float getPlayerAnimFrameRate(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getAnimFrameRate();
}

float getPlayerSubAnimFrame(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getSubAnimFrame();
}

float getPlayerSubAnimFrameMax(PlayerActorBase* player) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getSubAnimFrameMax();
}

float getPlayerBlendWeight(PlayerActorBase* player, int index) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return 0.0f;
    }
    return animator->getBlendWeight(index);
}

void setPlayerAnimRate(PlayerActorBase* player, float rate) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setAnimRate(rate);
}

void setPlayerAnimRateCommon(PlayerActorBase* player, float rate) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setAnimRateCommon(rate);
}

void setPlayerAnimFrame(PlayerActorBase* player, float frame) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setAnimFrame(frame);
}

void setPlayerAnimFrameCommon(PlayerActorBase* player, float frame) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setAnimFrameCommon(frame);
}

void setPlayerSubAnimFrame(PlayerActorBase* player, float frame) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setSubAnimFrame(frame);
}

void setPlayerSubAnimRate(PlayerActorBase* player, float rate) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setSubAnimRate(rate);
}

void setPlayerBlendWeight(PlayerActorBase* player, float w0, float w1, float w2, float w3, float w4, float w5) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setBlendWeight(w0, w1, w2, w3, w4, w5);
}

void setPlayerModelAlpha(PlayerActorBase* player, float alpha) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setModelAlpha(alpha);
}

void setPlayerPartsAnimRate(PlayerActorBase* player, float rate, const char* partsName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setPartsAnimRate(rate, partsName);
}

void setPlayerPartsAnimFrame(PlayerActorBase* player, float frame, const char* partsName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->setPartsAnimFrame(frame, partsName);
}

bool isPlayerUpperBodyAnim(PlayerActorBase* player, const char* animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return false;
    }
    if (animator->isUpperBodyAnimAttached()) {
        return animator->getCurrentUpperAnim() == animName;
    }
    return false;
}

void tryStartUpperAnim(PlayerActorBase* player, const char* animName) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    if (animator->isUpperBodyAnimAttached()) {
        return;
    }
    animator->startUpperBodyAnimAndHeadVisKeep(animName);
}

void tryStartUpperAnim(PlayerActorBase* player, const char* animName, int resetFrame) {
    PlayerAnimator* animator = player->getDemoAnimator();
    if (animator == nullptr) {
        return;
    }
    if (ml::isPlayerUpperBodyAnim(player, animName)) {
        animator->setAnimFrame(resetFrame);
        return;
    }
    animator->startUpperBodyAnimAndHeadVisKeep(animName);
}

}
