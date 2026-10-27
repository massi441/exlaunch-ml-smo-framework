#include <ml/CoreSMO/Player/PlayerUtil.h>

#include <Library/Effect/EffectSystemInfo.h>
#include <Library/LiveActor/ActorModelFunction.h>
#include <Library/LiveActor/ActorMovementFunction.h>
#include <Library/LiveActor/ActorPoseUtil.h>
#include <Library/LiveActor/LiveActorFunction.h>
#include <Library/Player/PlayerUtil.h>
#include <ml/Core/String/StringUtil.h>
#include <ml/CoreSMO/Player/PlayerAnimUtil.h>
#include <ml/CoreSMO/Util/ActionUtil.h>
#include <ml/CoreSMO/Util/SceneUtil.h>
#include <ml/Log/Log.h>
#include <Player/HackCap.h>
#include <Player/IUsePlayerPuppet.h>
#include <Player/PlayerCapManHeroEyesControl.h>
#include <Player/PlayerExternalVelocity.h>
#include <Player/PlayerFunction.h>
#include <Player/PlayerInitInfo.h>
#include <Player/PlayerModelChangerHakoniwa.h>
#include <Player/PlayerModelHolder.h>
#include <Player/PlayerPushReceiver.h>
#include <Player/PlayerStainControl.h>
#include <Player/PlayerTrigger.h>
#include <Scene/StageScene.h>
#include <System/GameDataFunction.h>
#include <Util/ObjUtil.h>
#include <Util/PlayerCollisionUtil.h>
#include <Util/PlayerUtil.h>

namespace ml {

namespace {

constexpr const char* NormalModelEntryName = "Normal";
constexpr const char* HeadSubActorName = "頭";
constexpr const char* HeroEyesSubActorName = "キャップの目";
constexpr const char* LeftHandSubActorName = "左手";
constexpr const char* RightHandSubActorName = "右手";

}

PlayerActorBase* getMainPlayerActor() {
    return static_cast<PlayerActorBase*>(rs::getPlayerActor(ml::getCurrentScene()));
}

PlayerActorBase* getPlayerActor(int slot) {
    return static_cast<PlayerActorBase*>(al::getPlayerActor(ml::getMainPlayerActor(), slot));
}

PlayerActorBase* tryFindNearestPlayerActor(const al::LiveActor* actor) {
    return static_cast<PlayerActorBase*>(al::tryFindNearestPlayerActor(actor));
}

const sead::Vector3f& getMainPlayerPos() {
    return al::getTrans(ml::getMainPlayerActor());
}

void resetPlayerPosition(PlayerActorHakoniwa* player, const sead::Vector3f& position) {
    al::resetPosition(player, position);

    player->getModelChanger()->resetPosition();
    player->getExternalVelocity()->reset();
    player->getPushReceiver()->clear();

    rs::resetCollision(player->getPlayerCollision());
}

void updateCostumeInitInfo(const PlayerInitInfo& playerInfo, const char* bodyName, const char* capName) {
    PlayerInitInfo& mutableInfo = const_cast<PlayerInitInfo&>(playerInfo);

    mutableInfo.bodyCostume = bodyName;
    mutableInfo.capCostume = capName;
}

bool wearCostume(const PlayerActorHakoniwa* player, const char* holderEntryName) {
    PlayerModelHolder* modelHolder = player->getModelHolder();

    al::LiveActor* newModelActor = modelHolder->tryFindModelActor(holderEntryName);
    if (newModelActor == nullptr) {
        LOG_TRACE("Model %s doesn't exist", holderEntryName);
        return false;
    }

    al::LiveActor* currentModelActor = ml::getPlayerModel(player);
    if (newModelActor == currentModelActor) {
        LOG_TRACE("Player is already wearing %s, ignoring it", holderEntryName);
        return false;
    }

    ml::tryCopyAction(currentModelActor, newModelActor);

    al::LiveActor* oldEyesActor = ml::getPlayerHeroEyes(player);
    if (oldEyesActor) {
        oldEyesActor->makeActorDead();
    }

    modelHolder->changeModel(holderEntryName);
    player->getModelChanger()->changeModel(newModelActor);

    al::LiveActor* newEyesActor = ml::getPlayerHeroEyes(player);
    if (newEyesActor) {
        newEyesActor->makeActorAlive();
        player->getHeroEyesControl()->setEyesActor(newEyesActor);
    }

    al::LiveActor* headActor = ml::getPlayerHead(player);
    if (headActor) {
        if (al::isExistJoint(headActor, "Hair")) {
            al::setJointVisibility(headActor, "Hair", false);
        }

        if (al::isExistJoint(headActor, "CapHair")) {
            al::setJointVisibility(headActor, "CapHair", true);
        }
    }

    player->getStainControl()->setPlayerModel(newModelActor);

    return true;
}

bool wearNormalCostume(const PlayerActorHakoniwa* player) {
    return ml::wearCostume(player, NormalModelEntryName);
}

const char* getCurrentCostumeName(const PlayerActorHakoniwa* player) {
    return player->getModelHolder()->getCurrentEntry()->name.cstr();
}

const char* getCurrentPlayerModelName(const PlayerActorHakoniwa* player) {
    PlayerModelHolder::Entry* currentModel = player->getModelHolder()->getCurrentEntry();
    if (currentModel == nullptr) {
        return nullptr;
    }

    return currentModel->name.cstr();
}

bool isPlayerCurrentModel(const PlayerActorHakoniwa* player, const char* modelName) {
    const char* currentModel = ml::getCurrentPlayerModelName(player);
    return currentModel && ml::streql(currentModel, modelName);
}

al::LiveActor* getPlayerModel(const PlayerActorHakoniwa* player, const char* entryName) {
    return player->getModelHolder()->tryFindModelActor(entryName);
}

al::LiveActor* getPlayerModel(const PlayerActorHakoniwa* player) {
    return player->getModelHolder()->getCurrentActor();
}

al::LiveActor* getPlayerHead(const PlayerActorHakoniwa* player) {
    al::LiveActor* modelActor = ml::getPlayerModel(player);
    if (modelActor == nullptr) {
        return nullptr;
    }

    return al::getSubActor(modelActor, HeadSubActorName);
}

al::LiveActor* getPlayerHeroEyes(const PlayerActorHakoniwa* player, const char* entryName) {
    al::LiveActor* modelActor = ml::getPlayerModel(player, entryName);
    if (modelActor == nullptr) {
        return nullptr;
    }

    al::LiveActor* headActor = al::getSubActor(modelActor, HeadSubActorName);
    if (headActor == nullptr) {
        return nullptr;
    }

    return al::getSubActor(headActor, HeroEyesSubActorName);
}

al::LiveActor* getPlayerHeroEyes(const PlayerActorHakoniwa* player) {
    return ml::getPlayerHeroEyes(player, ml::getCurrentPlayerModelName(player));
}

al::LiveActor* getPlayerLeftHand(const PlayerActorHakoniwa* player) {
    al::LiveActor* modelActor = ml::getPlayerModel(player);
    if (modelActor == nullptr) {
        return nullptr;
    }

    return al::getSubActor(modelActor, LeftHandSubActorName);
}

al::LiveActor* getPlayerRightHand(const PlayerActorHakoniwa* player) {
    al::LiveActor* modelActor = ml::getPlayerModel(player);
    if (modelActor == nullptr) {
        return nullptr;
    }

    return al::getSubActor(modelActor, RightHandSubActorName);
}

bool isPlayerTriggerDeath(const PlayerActorHakoniwa* player) {
    return player->mTrigger->isOnAnyDamage() && GameDataFunction::getPlayerHitPoint(player) == 1;
}

void killPlayer(PlayerActorBase* playerActor, PlayerDeathType deathType) {
    GameDataFunction::killPlayer(GameDataHolderWriter(playerActor));
    playerActor->startDemoPuppetable();
    al::setVelocityZero(playerActor);
    rs::faceToCamera(playerActor);

    ml::endPlayerSubAnim(playerActor);

    if (deathType == PlayerDeathType::Random) {
        ml::startPlayerAnimDead(playerActor);
    } else {
        ml::startPlayerAnim(playerActor, PlayerDeathTypeData::ToString(deathType));
    }
}

bool isPlayer3d(const PlayerActorHakoniwa* player) {
    return !player->getModelChanger()->is2DModel();
}

PlayerCostumeInfo* initMarioModelActorNoCloset(al::LiveActor* modelActor, const al::ActorInitInfo& initInfo, const char* costumeBodyName, const char* capCostumeName, al::AudioKeeper* audioKeeper) {
    return PlayerFunction::initMarioModelActor(modelActor, initInfo, costumeBodyName, capCostumeName, audioKeeper, false);
}

bool initAndRegisterMarioModel(const PlayerActorHakoniwa* player, const char* modelActorEntryName, const al::ActorInitInfo& initInfo, const char* costumeBodyName, const char* capCostumeName) {
    PlayerModelHolder* modelHolder = player->getModelHolder();

    if (modelHolder->isFull()) {
        return false;
    }

    al::LiveActor* modelActor = new al::LiveActor(modelActorEntryName);
    PlayerCostumeInfo* costumeInfo = ml::initMarioModelActorNoCloset(modelActor, initInfo, costumeBodyName, capCostumeName, player->getAudioKeeper());

    if (costumeInfo == nullptr) {
        return false;
    }

    modelHolder->registerModel(modelActor, modelActorEntryName);

    al::LiveActor* heroEyesActor = ml::getPlayerHeroEyes(player, modelActorEntryName);
    if (heroEyesActor) {
        heroEyesActor->kill();
    }

    return true;
}

void copyPoseToPuppet(const al::LiveActor* sourceActor, IUsePlayerPuppet* puppet) {
    sead::Quatf quat;
    al::calcQuat(&quat, sourceActor);

    puppet->setPose(quat);
}

void setPlayerScale(PlayerActorHakoniwa* player, float scale) {
    sead::Vector3f scaleVec = sead::Vector3f(scale, scale, scale);

    al::setScale(player, scaleVec);
    al::setScale(player->getHackCap(), scaleVec);
}

void emitPlayerEffect(const PlayerActorHakoniwa* player, const char* effectName) {
    al::emitEffectCurrentPos(ml::getPlayerModel(player), effectName);
}

void emitPlayerEffect(const PlayerActorHakoniwa* player, const char* effectName, const sead::Vector3f* transPtr) {
    al::emitEffect(ml::getPlayerModel(player), effectName, transPtr);
}

void setPlayerEffectScale(const PlayerActorHakoniwa* player, const char* effectName, const sead::Vector3f& scale) {
    al::setEffectAllScale(ml::getPlayerModel(player), effectName, scale);
}

void stopPlayerEffectsAll(const PlayerActorHakoniwa* player) {
    al::deleteEffectAll(ml::getPlayerModel(player));
}

}
