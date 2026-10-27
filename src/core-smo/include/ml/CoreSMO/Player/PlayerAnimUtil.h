#pragma once

#include <prim/seadSafeString.h>

class PlayerActorBase;

namespace ml {

void startPlayerAnim(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerAnimCommon(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerAnimSpinAttack(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerSubAnim(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerSubAnimOnlyAir(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerUpperBodyAnim(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerUpperBodyAnimSubParts(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerUpperBodyAnimAndHeadVisKeep(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerAnimDead(PlayerActorBase* player);
void startPlayerPartsAnim(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerPartsPartialAnim(PlayerActorBase* player, const sead::SafeString& animName);
void startPlayerRightHandAnim(PlayerActorBase* player, const char* animName);
void startPlayerEyeControlAnim(PlayerActorBase* player, bool value);
void startPlayerPress(PlayerActorBase* player);
void startPlayerSnapShotMode(PlayerActorBase* player);

void endPlayerSubAnim(PlayerActorBase* player);
void endPlayerEyeControlAnim(PlayerActorBase* player, int value);
void endPlayerSnapShotMode(PlayerActorBase* player);
void endPlayerDemoInvalidateModelAlpha(PlayerActorBase* player);

void updatePlayerAnimFrame(PlayerActorBase* player);
void updatePlayerModel(PlayerActorBase* player);
void updatePlayerModelAlpha(PlayerActorBase* player);
void updatePlayerEyeControlAnim(PlayerActorBase* player);

void clearPlayerUpperBodyAnim(PlayerActorBase* player);
void clearPlayerInterpolation(PlayerActorBase* player);
void clearPlayerEndEyeControlAnimDelay(PlayerActorBase* player);

void copyPlayerAnim(PlayerActorBase* player);
void copyPlayerAnimLocal(PlayerActorBase* player);

void applyPlayerBlendWeight(PlayerActorBase* player);
void forcePlayerCapOn(PlayerActorBase* player);
void forcePlayerCapOff(PlayerActorBase* player);
void overwridePlayerYoshiEatVis(PlayerActorBase* player);
void restartPlayerYoshiActionVis(PlayerActorBase* player);
void recordPlayerRunStartAnimRate(PlayerActorBase* player, float rate);
void resetPlayerModelAlpha(PlayerActorBase* player);

bool isPlayerAnim(PlayerActorBase* player, const sead::SafeString& animName);
bool isPlayerAnimEnd(PlayerActorBase* player);
bool isPlayerSubAnim(PlayerActorBase* player, const sead::SafeString& subAnimName);
bool isPlayerSubAnimEnd(PlayerActorBase* player);
bool isPlayerUpperBodyAnimAttached(PlayerActorBase* player);
bool isPlayerSubAnimPlaying(PlayerActorBase* player);

float getPlayerAnimFrame(PlayerActorBase* player);
float getPlayerAnimFrameMax(PlayerActorBase* player);
float getPlayerAnimFrameRate(PlayerActorBase* player);
float getPlayerSubAnimFrame(PlayerActorBase* player);
float getPlayerSubAnimFrameMax(PlayerActorBase* player);
float getPlayerBlendWeight(PlayerActorBase* player, int index);

void setPlayerAnimRate(PlayerActorBase* player, float rate);
void setPlayerAnimRateCommon(PlayerActorBase* player, float rate);
void setPlayerAnimFrame(PlayerActorBase* player, float frame);
void setPlayerAnimFrameCommon(PlayerActorBase* player, float frame);
void setPlayerSubAnimFrame(PlayerActorBase* player, float frame);
void setPlayerSubAnimRate(PlayerActorBase* player, float rate);
void setPlayerBlendWeight(PlayerActorBase* player, float w0, float w1, float w2, float w3, float w4, float w5);
void setPlayerModelAlpha(PlayerActorBase* player, float alpha);
void setPlayerPartsAnimRate(PlayerActorBase* player, float rate, const char* partsName);
void setPlayerPartsAnimFrame(PlayerActorBase* player, float frame, const char* partsName);

// custom funcs
bool isPlayerUpperBodyAnim(PlayerActorBase* player, const char* animName);
void tryStartUpperAnim(PlayerActorBase* player, const char* animName);
void tryStartUpperAnim(PlayerActorBase* player, const char* animName, int resetFrame);

}
