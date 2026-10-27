#pragma once

#include <math/seadVector.h>

namespace al {
class LiveActor;
class LiveActorGroup;
}

namespace ml {

void killIfAlive(al::LiveActor* actor);
void appearIfDead(al::LiveActor* actor);
bool isActorNamed(const al::LiveActor* actor, const char* name);

bool isAbovePlayer(const al::LiveActor* actor);
bool isAbovePlayerThresh(const al::LiveActor* actor, float threshold);

float getTransX(const al::LiveActor* actor);
float getTransY(const al::LiveActor* actor);
float getTransZ(const al::LiveActor* actor);
float getScaleX(const al::LiveActor* actor);
float getScaleY(const al::LiveActor* actor);
float getScaleZ(const al::LiveActor* actor);
float getVelocityX(const al::LiveActor* actor);
float getVelocityY(const al::LiveActor* actor);
float getVelocityZ(const al::LiveActor* actor);
float getVelocity(const al::LiveActor* actor);
float getGravityX(const al::LiveActor* actor);
float getGravityY(const al::LiveActor* actor);
float getGravityZ(const al::LiveActor* actor);

void addTrans(al::LiveActor* actor, const sead::Vector3f& trans);

void addScale(al::LiveActor* actor, const sead::Vector3f& scale);
void addScaleX(al::LiveActor* actor, float scale);
void addScaleY(al::LiveActor* actor, float scale);
void addScaleZ(al::LiveActor* actor, float scale);
void addScale(al::LiveActor* actor, float scale);

/**
 * Sets the scale of an actor to 1
 */
void resetScale(al::LiveActor* actor);

void scaleVelocityFront(al::LiveActor* actor, float scale);

bool turnToNearestPlayer(al::LiveActor* actor, float rotateSpeed);
bool turnToNearestPlayer(al::LiveActor* actor, float nearPlayerDistance, float rotateSpeed);

bool isModelVisible(const al::LiveActor* actor);
bool changeActors(al::LiveActor* oldActor, al::LiveActor* newActor);

bool isFaceToTargetH(const al::LiveActor* actor, const sead::Vector3f& target, float degreeThreshold = 0.1f);

void forEachActor(const al::LiveActorGroup* group, void (al::LiveActor::*func)());
void forEachActor(const al::LiveActorGroup* group, void (*func)(al::LiveActor*));

sead::Vector3f getDirToTarget(const al::LiveActor* actor, const sead::Vector3f& target);
sead::Vector3f getDirToActor(const al::LiveActor* actor, const sead::Vector3f& pos);
sead::Vector3f getFrontDir(const al::LiveActor* actor);
sead::Vector3f getBackDir(const al::LiveActor* actor);
sead::Vector3f getUpDir(const al::LiveActor* actor);
sead::Vector3f getDownDir(const al::LiveActor* actor);
sead::Vector3f getSideDir(const al::LiveActor* actor);

}
