#include <ml/CoreSMO/Util/NerveUtil.h>

#include <Library/Nerve/Nerve.h>
#include <Library/Nerve/NerveKeeper.h>
#include <Library/Nerve/NerveUtil.h>
#include <ml/Core/Util/Util.h>
#include <ml/Hook/HookUtil.h>

namespace ml {

u64 getNerveOffset(const al::IUseNerve* nerveUser) {
    return ml::getNerveOffset(al::getCurrentNerve(nerveUser));
}

u64 getNerveOffset(const al::Nerve* nerve) {
    return reinterpret_cast<u64>(nerve) - ml::getBaseAddress();
}

const al::Nerve* getNerveAt(u64 offset) {
    return ml::getRuntimePtr<const al::Nerve*>(offset);
}

bool isNotNerve(const al::IUseNerve* nerveUser, al::Nerve* nerve) {
    return !al::isNerve(nerveUser, nerve);
}

bool setNerveIfNotAlready(al::IUseNerve* nerveUser, const al::Nerve* nerve) {
    if (!al::isNerve(nerveUser, nerve)) {
        al::setNerve(nerveUser, nerve);
        return true;
    }

    return false;
}

bool setNerveIfNotAlready(al::IUseNerve* nerveUser, const al::Nerve* nerve, int minimumSteps) {
    if (!al::isNerve(nerveUser, nerve) || al::isGreaterEqualStep(nerveUser, minimumSteps)) {
        al::setNerve(nerveUser, nerve);
        return true;
    }

    return false;
}

const char* getCurrentNerveName(const al::IUseNerve* nerveUser) {
    return ml::getTypeId(al::getCurrentNerve(nerveUser));
}

bool isStepInterval(const al::IUseNerve* nerveUser, int stepInterval) {
    return al::getNerveStep(nerveUser) % stepInterval == 0;
}

bool isEnterNerve(const al::IUseNerve* nerveUser, const al::Nerve* nerve) {
    return al::isNerve(nerveUser, nerve) && al::isFirstStep(nerveUser);
}

bool isNerveAtStep(const al::IUseNerve* nerveUser, const al::Nerve* nerve, int step) {
    return al::isNerve(nerveUser, nerve) && al::isStep(nerveUser, step);
}

bool isFirstStep(al::NerveKeeper* nerveKeeper) {
    return nerveKeeper->getCurrentStep() == 0;
}

}
