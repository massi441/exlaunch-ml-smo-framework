#pragma once

#include <basis/seadTypes.h>

namespace al {
class IUseNerve;
class Nerve;
class NerveKeeper;
}

namespace ml {

/**
 * Returns the offset of the current nerve of a nerve user in the game binary
 */
u64 getNerveOffset(const al::IUseNerve* nerveUser);

/**
 * Returns the offset of a nerve in the game binary. Useful to find a nerve in Ghidra
 */
u64 getNerveOffset(const al::Nerve* nerve);

/**
 * Returns the game's nerve found at an offset in the game binary
 * @param offset The offset of the nerve in the game binary
 */
const al::Nerve* getNerveAt(u64 offset);

/**
 * Checks if the current step of the nerve is a multiple of the interval, e.g. every 60 steps
 */
bool isStepInterval(const al::IUseNerve* nerveUser, int stepInterval);

/**
 * Checks if an actor is not in a given nerve
 */
bool isNotNerve(const al::IUseNerve* nerveUser, al::Nerve* nerve);

/**
 * Sets the nerve, unless the nerve user is already in it. Returns true if the nerve was set
 */
bool setNerveIfNotAlready(al::IUseNerve* nerveUser, const al::Nerve* nerve);

/**
 * Sets the nerve if the nerve user is in another nerve. If it's already in that nerve, the nerve is
 * only restarted once it has run for at least the minimum steps. Returns true if the nerve was set
 * @param nerveUser The nerve user to set the nerve of
 * @param nerve The nerve to set
 * @param minimumSteps The minimum steps the nerve has to run before it can be restarted
 */
bool setNerveIfNotAlready(al::IUseNerve* nerveUser, const al::Nerve* nerve, int minimumSteps);

/**
 * Returns the type if name of an IUseNerve's current nerve. Must compile with RTTI on.
 */
const char* getCurrentNerveName(const al::IUseNerve* nerveUser);

/**
 * Checks if a nerve user is in the first step of a given nerve
 */
bool isEnterNerve(const al::IUseNerve* nerveUser, const al::Nerve* nerve);

/**
 * Checks if a nerve user is at a given step
 */
bool isNerveAtStep(const al::IUseNerve* nerveUser, const al::Nerve* nerve, int step);

/**
 * Checks if a NerveKeeper is in its first step
 */
bool isFirstStep(al::NerveKeeper* nerveKeeper);

}
