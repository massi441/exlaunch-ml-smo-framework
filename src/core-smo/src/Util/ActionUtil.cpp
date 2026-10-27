#include <ml/CoreSMO/Util/ActionUtil.h>

#include <Library/LiveActor/ActorActionFunction.h>

namespace ml {

bool startActionIfExist(al::LiveActor* actor, const char* actionName) {
    if (al::isExistAction(actor, actionName)) {
        al::startAction(actor, actionName);
        return true;
    }

    return false;
}

void startActionWithRate(al::LiveActor* actor, const char* actionName, float rate) {
    al::startAction(actor, actionName);
    al::setActionFrameRate(actor, rate);
}

bool tryCopyAction(al::LiveActor* source, al::LiveActor* destination) {
    if (al::getActionName(source) == nullptr) {
        return false;
    }

    al::copyAction(destination, source);
    return true;
}

bool isExistAndEndAction(const al::LiveActor* actor) {
    if (al::getActionName(actor)) {
        return al::isActionEnd(actor);
    }

    return false;
}

}
