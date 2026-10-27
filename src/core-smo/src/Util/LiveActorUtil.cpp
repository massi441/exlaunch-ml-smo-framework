#include <ml/CoreSMO/Util/LiveActorUtil.h>

#include <cstring>
#include <Library/LiveActor/ActorFlagFunction.h>
#include <Library/LiveActor/ActorModelFunction.h>
#include <Library/LiveActor/ActorMovementFunction.h>
#include <Library/LiveActor/ActorPoseUtil.h>
#include <Library/LiveActor/LiveActor.h>
#include <Library/LiveActor/LiveActorGroup.h>
#include <Library/Player/PlayerUtil.h>

namespace ml {

void killIfAlive(al::LiveActor* actor) {
    if (al::isAlive(actor)) {
        actor->kill();
    }
}

void appearIfDead(al::LiveActor* actor) {
    if (al::isDead(actor)) {
        actor->appear();
    }
}

bool isActorNamed(const al::LiveActor* actor, const char* name) {
    return strcmp(actor->getName(), name) == 0;
}

bool isAbovePlayer(const al::LiveActor* actor) {
    al::LiveActor* player = al::tryFindNearestPlayerActor(actor);

    if (player) {
        return al::getTrans(actor).y >= al::getTrans(player).y;
    }

    return false;
}

bool isAbovePlayerThresh(const al::LiveActor* actor, float threshold) {
    al::LiveActor* player = al::tryFindNearestPlayerActor(actor);

    if (player) {
        float minTrans = al::getTrans(player).y + threshold;
        return al::getTrans(actor).y >= minTrans;
    }

    return false;
}

float getTransX(const al::LiveActor* actor) {
    return al::getTrans(actor).x;
}

float getTransY(const al::LiveActor* actor) {
    return al::getTrans(actor).y;
}

float getTransZ(const al::LiveActor* actor) {
    return al::getTrans(actor).z;
}

float getScaleX(const al::LiveActor* actor) {
    return al::getScale(actor).x;
}

float getScaleY(const al::LiveActor* actor) {
    return al::getScale(actor).y;
}

float getScaleZ(const al::LiveActor* actor) {
    return al::getScale(actor).z;
}

float getVelocityX(const al::LiveActor* actor) {
    return al::getVelocity(actor).x;
}

float getVelocityY(const al::LiveActor* actor) {
    return al::getVelocity(actor).y;
}

float getVelocityZ(const al::LiveActor* actor) {
    return al::getVelocity(actor).z;
}

float getVelocity(const al::LiveActor* actor) {
    return al::getVelocity(actor).length();
}

float getGravityX(const al::LiveActor* actor) {
    return al::getGravity(actor).x;
}

float getGravityY(const al::LiveActor* actor) {
    return al::getGravity(actor).y;
}

float getGravityZ(const al::LiveActor* actor) {
    return al::getGravity(actor).z;
}

void addTrans(al::LiveActor* actor, const sead::Vector3f& trans) {
    *al::getTransPtr(actor) += trans;
}

void addScale(al::LiveActor* actor, const sead::Vector3f& scale) {
    *al::getScalePtr(actor) += scale;
}

void addScaleX(al::LiveActor* actor, float scale) {
    al::getScalePtr(actor)->x += scale;
}

void addScaleY(al::LiveActor* actor, float scale) {
    al::getScalePtr(actor)->y += scale;
}

void addScaleZ(al::LiveActor* actor, float scale) {
    al::getScalePtr(actor)->z += scale;
}

void addScale(al::LiveActor* actor, float scale) {
    ml::addScale(actor, sead::Vector3f(scale, scale, scale));
}

void resetScale(al::LiveActor* actor) {
    al::setScaleAll(actor, 1.0f);
}

void scaleVelocityFront(al::LiveActor* actor, float scale) {
    sead::Vector3f frontDir;
    al::calcFrontDir(&frontDir, actor);

    al::scaleVelocityDirection(actor, frontDir, scale);
}

bool turnToNearestPlayer(al::LiveActor* actor, float rotateSpeed) {
    al::LiveActor* player = al::tryFindNearestPlayerActor(actor);

    if (player == nullptr) {
        return false;
    }

    al::turnToTarget(actor, player, rotateSpeed);
    return true;
}

bool turnToNearestPlayer(al::LiveActor* actor, float nearPlayerDistance, float rotateSpeed) {
    if (!al::isNearPlayer(actor, nearPlayerDistance)) {
        return false;
    }

    return ml::turnToNearestPlayer(actor, rotateSpeed);
}

bool isModelVisible(const al::LiveActor* actor) {
    return !al::isHideModel(actor);
}

bool changeActors(al::LiveActor* oldActor, al::LiveActor* newActor) {
    if (oldActor->getPoseKeeper() == nullptr || newActor->getPoseKeeper() == nullptr) {
        return false;
    }

    al::copyPose(newActor, oldActor);

    oldActor->kill();
    newActor->appear();

    return true;
}

bool isFaceToTargetH(const al::LiveActor* actor, const sead::Vector3f& target, float degreeThreshold) {
    sead::Vector3f frontDir;
    al::calcFrontDir(&frontDir, actor);

    return al::isFaceToTargetDegreeH(actor, target, frontDir, degreeThreshold);
}

void forEachActor(const al::LiveActorGroup* group, void (al::LiveActor::*func)()) {
    for (al::LiveActor* actor : *group) {
        (actor->*func)();
    }
}

void forEachActor(const al::LiveActorGroup* group, void (*func)(al::LiveActor*)) {
    for (al::LiveActor* actor : *group) {
        func(actor);
    }
}

sead::Vector3f getDirToTarget(const al::LiveActor* actor, const sead::Vector3f& target) {
    sead::Vector3f direction = target - al::getTrans(actor);
    direction.normalize();
    return direction;
}

sead::Vector3f getDirToActor(const al::LiveActor* actor, const sead::Vector3f& pos) {
    sead::Vector3f direction = al::getTrans(actor) - pos;
    direction.normalize();
    return direction;
}

sead::Vector3f getFrontDir(const al::LiveActor* actor) {
    sead::Vector3f frontDir;
    al::calcFrontDir(&frontDir, actor);
    return frontDir;
}

sead::Vector3f getBackDir(const al::LiveActor* actor) {
    sead::Vector3f backDir;
    al::calcBackDir(&backDir, actor);
    return backDir;
}

sead::Vector3f getUpDir(const al::LiveActor* actor) {
    sead::Vector3f upDir;
    al::calcUpDir(&upDir, actor);
    return upDir;
}

sead::Vector3f getDownDir(const al::LiveActor* actor) {
    sead::Vector3f downDir;
    al::calcDownDir(&downDir, actor);
    return downDir;
}

sead::Vector3f getSideDir(const al::LiveActor* actor) {
    sead::Vector3f sideDir;
    al::calcSideDir(&sideDir, actor);
    return sideDir;
}

}
