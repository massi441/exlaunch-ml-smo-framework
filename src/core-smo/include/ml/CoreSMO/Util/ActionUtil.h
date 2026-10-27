#pragma once

namespace al {
class LiveActor;
}

namespace ml {

bool startActionIfExist(al::LiveActor* actor, const char* actionName);
void startActionWithRate(al::LiveActor* actor, const char* actionName, float rate);
bool tryCopyAction(al::LiveActor* source, al::LiveActor* destination);
bool isExistAndEndAction(const al::LiveActor* actor);

}
