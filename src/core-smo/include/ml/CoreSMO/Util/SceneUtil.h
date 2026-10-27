#pragma once

#include <Library/Scene/Scene.h>

class HakoniwaSequence;
namespace al {
class Resource;
class ExecuteDirector;
class Scene;
}

namespace ml {

/**
 * Returns the scene currently run by the game's sequence
 */
al::Scene* getCurrentScene();

/**
 * Returns the execute director of the current scene
 */
al::ExecuteDirector* getCurrentSceneExecuteDirector();

/**
 * Requests a change to another stage and goes to it immediately
 * @param stageName The name of the stage to go to
 * @param scene The scene requesting the change
 * @param scenario The scenario to start the stage in. -1 keeps the game's default scenario
 * @return true if the stage change was accepted
 */
bool goToStage(const char* stageName, al::Scene* scene = ml::getCurrentScene(), int scenario = -1);

/**
 * Restarts the current stage immediately, by changing to the stage the scene is already in
 * @return true if the stage change was accepted
 */
bool reloadScene(al::Scene* scene = ml::getCurrentScene());

const char* getCurrentStageName(const al::Scene* scene = ml::getCurrentScene());

/**
 * Checks if the sequence is in its play stage nerve, meaning a stage is running, rather than loading or showing a menu
 */
bool isPlayingStage(const HakoniwaSequence* sequence);

/**
 * Returns the director that owns the stage switches of a scene
 */
al::StageSwitchDirector* getStageSwitchDirector(const al::Scene* scene = ml::getCurrentScene());

/**
 * Returns the resource archive of one of the scene's map stages
 * @param scene The scene to get the stage resource of
 * @param idx The index of the map stage. 0 is the main stage
 */
al::Resource* getStageResource(const al::Scene* scene = ml::getCurrentScene(), int idx = 0);

}
