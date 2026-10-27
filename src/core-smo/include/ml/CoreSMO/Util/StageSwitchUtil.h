#pragma once

#include <Library/Stage/StageSwitchUtil.h>
#include <ml/CoreSMO/Misc/Functor.h>
#include <ml/CoreSMO/Util/LiveActorUtil.h>

namespace ml {

/**
 * Initializes an actor's switch appear if a SwitchAppear link is present. If the actor is already alive, it will be killed and will appear when the switch is activated.
 * If no SwitchAppear link is present, the actor will appear if it is dead.
 * @tparam T The type of the actor
 * @param actor The actor to initialize
 * @return True if the stage switch was initialized, false otherwise
 */
template <LiveActorType T>
bool initSwitchAppear(T* actor) {
    if (al::listenStageSwitchOnAppear(actor, LiveActorFunctor<T>(actor, &T::appear))) {
        ml::killIfAlive(actor);
        return true;
    }

    ml::appearIfDead(actor);

    return false;
}

/**
 * Initializes an actor's switch kill if a SwitchKill link is present. The actor will be killed when the switch is activated.
 * @tparam T The type of the actor
 * @param actor The actor to initialize
 * @return True if the stage switch was initialized, false otherwise
 */
template <LiveActorType T>
bool initSwitchKill(T* actor) {
    if (al::isValidSwitchKill(actor)) {
        return al::listenStageSwitchOnKill(actor, LiveActorFunctor<T>(actor, &T::kill));
    }

    return false;
}

/**
 * Initializes both the switch appear and switch kill of an actor. If both links are present, the actor is killed and
 * will appear and be killed as the switches are activated. Otherwise, each link present is initialized on its own.
 * @tparam T The type of the actor
 * @param actor The actor to initialize
 */
template <LiveActorType T>
void initSwitchAppearAndKill(T* actor) {
    bool isSwitchAppear = al::isValidSwitchAppear(actor);
    bool isSwitchKill = al::isValidSwitchKill(actor);

    if (isSwitchAppear && isSwitchKill) {
        al::listenStageSwitchOnAppear(actor, LiveActorFunctor<T>(actor, &T::appear));
        al::listenStageSwitchOnKill(actor, LiveActorFunctor<T>(actor, &T::kill));

        return ml::killIfAlive(actor);
    }

    ml::initSwitchAppear(actor);
    ml::initSwitchKill(actor);
}

/**
 * Calls the given function when the actor's SwitchKill switch is activated, if a SwitchKill link is present.
 * @tparam T The type of the actor
 * @param actor The actor listening to the switch
 * @param func The member function to call when the switch is activated
 */
template <LiveActorType T>
void initSwitchOnKill(T* actor, LiveActorFunc<T> func) {
    if (al::isValidSwitchKill(actor)) {
        al::listenStageSwitchOnKill(actor, LiveActorFunctor<T>(actor, func));
    }
}

/**
 * Calls the given function when the actor's SwitchStart switch is activated, if a SwitchStart link is present.
 * @tparam T The type of the actor
 * @param actor The actor listening to the switch
 * @param func The member function to call when the switch is activated
 */
template <LiveActorType T>
void initSwitchStart(T* actor, LiveActorFunc<T> func) {
    if (al::isValidSwitchStart(actor)) {
        al::listenStageSwitchOnStart(actor, LiveActorFunctor<T>(actor, func));
    }
}

/**
 * Calls the given function when the named stage switch is activated, if the actor has a link with that name.
 * @tparam T The type of the actor
 * @tparam R The return type of the function
 * @param actor The actor listening to the switch
 * @param switchLinkName The name of the switch link
 * @param func The member function to call when the switch is activated
 * @return True if the stage switch was initialized, false otherwise
 */
template <LiveActorType T, typename R>
bool initStageSwitch(T* actor, const char* switchLinkName, LiveActorFunc<T, R> func) {
    if (al::isValidStageSwitch(actor, switchLinkName)) {
        al::listenStageSwitchOn(actor, switchLinkName, LiveActorFunctor<T, R>(actor, func));
        return true;
    }

    return false;
}

/**
 * Const member function overload of initStageSwitch.
 * @tparam T The type of the actor
 * @tparam R The return type of the function
 * @param actor The actor listening to the switch
 * @param switchLinkName The name of the switch link
 * @param func The const member function to call when the switch is activated
 * @return True if the stage switch was initialized, false otherwise
 */
template <LiveActorType T, typename R>
bool initStageSwitch(T* actor, const char* switchLinkName, LiveActorConstFunc<T, R> func) {
    if (al::isValidStageSwitch(actor, switchLinkName)) {
        al::listenStageSwitchOn(actor, switchLinkName, LiveActorFunctorConst<T, R>(actor, func));
        return true;
    }

    return false;
}

}
