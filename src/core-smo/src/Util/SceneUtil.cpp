#include <ml/CoreSMO/Util/SceneUtil.h>

#include <Library/LiveActor/LiveActorKit.h>
#include <Library/Nerve/NerveUtil.h>
#include <Library/Scene/Scene.h>
#include <Library/Scene/SceneUtil.h>
#include <Library/Sequence/Sequence.h>
#include <Library/Stage/StageResourceKeeper.h>
#include <Library/Stage/StageResourceList.h>
#include <MapObj/ChangeStageInfo.h>
#include <ml/CoreSMO/Util/NerveUtil.h>
#include <Scene/StageScene.h>
#include <Sequence/HakoniwaSequence.h>
#include <System/GameDataFunction.h>
#include <System/GameSystem.h>

namespace ml {

namespace {

constexpr u64 HakoniwaPlayStageNerveOffset = 0x1d977d0;

}

al::Scene* getCurrentScene() {
    return GameSystemFunction::getGameSystem()->getSequence()->getCurrentScene();
}

al::ExecuteDirector* getCurrentSceneExecuteDirector() {
    return al::getSceneExecuteDirector(ml::getCurrentScene());
}

bool goToStage(const char* stageName, al::Scene* scene, int scenario) {
    GameDataHolder* dataHolder = GameDataFunction::getGameDataHolder(scene);
    ChangeStageInfo changeStageInfo = ChangeStageInfo(dataHolder, nullptr, stageName, false, scenario);
    GameDataFunction::tryChangeNextStage(scene, &changeStageInfo);

    return rs::tryChangeNextStage(dataHolder, scene);
}

bool reloadScene(al::Scene* scene) {
    GameDataHolder* dataHolder = GameDataFunction::getGameDataHolder(scene);
    ChangeStageInfo changeStageInfo = ChangeStageInfo(dataHolder, nullptr, GameDataFunction::getCurrentStageName(scene), false);
    GameDataFunction::tryChangeNextStage(scene, &changeStageInfo);

    return rs::tryChangeNextStage(dataHolder, scene);
}

const char* getCurrentStageName(const al::Scene* scene) {
    return GameDataFunction::getCurrentStageName(scene);
}

bool isPlayingStage(const HakoniwaSequence* sequence) {
    static const al::Nerve* nrvHakoniwaPlayStage = ml::getNerveAt(HakoniwaPlayStageNerveOffset);
    return al::isNerve(sequence, nrvHakoniwaPlayStage);
}

al::StageSwitchDirector* getStageSwitchDirector(const al::Scene* scene) {
    return scene->getLiveActorKit()->getStageSwitchDirector();
}

al::Resource* getStageResource(const al::Scene* scene, int idx) {
    return scene->getStageResourceKeeper()->getMapStageInfo()->getStageInfo(idx)->getResource();
}

}
