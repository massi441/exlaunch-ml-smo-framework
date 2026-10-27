#pragma once

#include <ml/CoreSMO/Player/PlayerDeath.h>
#include <Player/PlayerActorHakoniwa.h>

class IUsePlayerPuppet;
class PlayerCostumeInfo;

namespace ml {

PlayerActorBase* getMainPlayerActor();
PlayerActorBase* getPlayerActor(int slot);
PlayerActorBase* tryFindNearestPlayerActor(const al::LiveActor* actor);

const sead::Vector3f& getMainPlayerPos();

template <typename T>
T* getMainPlayerActor() {
    return static_cast<T*>(ml::getMainPlayerActor());
}

template <typename T>
T* getPlayerActor(int index) {
    return static_cast<T*>(ml::getPlayerActor(index));
}

template <typename T>
T* tryFindNearestPlayerActor(const al::LiveActor* actor) {
    return static_cast<T*>(ml::tryFindNearestPlayerActor(actor));
}

/**
 * Places the player at a given position, synchronizing the collision subsystems in the process.
 * @param player The player to reset the position of
 * @param position The position to reset the player's position at
 */
void resetPlayerPosition(PlayerActorHakoniwa* player, const sead::Vector3f& position);

/**
 * Updates the costume information of a player. To use when you need to control the costume
 * Note: the constness is cast away from the player info. the function takes the info by const reference
 * for the callers not to have to manually type the const_cast each time.
 * @param playerInfo The player init info
 * @param bodyName The body name of the costume
 * @param capName The cap name of the costume
 */
void updateCostumeInitInfo(const PlayerInitInfo& playerInfo, const char* bodyName, const char* capName);

/**
 * Updates the current player's costume without requiring a scene reload
 * @param player The player to change the costume of
 * @param holderEntryName The name of the model with the costume. This model must be registered at init time
 * @return true if the costume was worn, false otherwise.
 */
bool wearCostume(const PlayerActorHakoniwa* player, const char* holderEntryName);

/**
 * Changes the player's model back to the "Normal" entry registered in the PlayerModelHolder
 * @param player The player to change the costume of
 * @return true if the model was changed, false otherwise
 */
bool wearNormalCostume(const PlayerActorHakoniwa* player);

/**
 * Returns the name of the current costume of the player
 */
const char* getCurrentCostumeName(const PlayerActorHakoniwa* player);

/**
 * Returns the name of the active model entry in the PlayerModelHolder
 */
const char* getCurrentPlayerModelName(const PlayerActorHakoniwa* player);

/**
 * Checks if a model is currently active in the PlayerModelHolder
 * @param player The player to check
 * @param modelName The name of the model to check
 * @return true if the current model is the requested model, false otherwise
 */
bool isPlayerCurrentModel(const PlayerActorHakoniwa* player, const char* modelName);

al::LiveActor* getPlayerModel(const PlayerActorHakoniwa* player, const char* entryName);
al::LiveActor* getPlayerModel(const PlayerActorHakoniwa* player);
al::LiveActor* getPlayerHead(const PlayerActorHakoniwa* player);
al::LiveActor* getPlayerHeroEyes(const PlayerActorHakoniwa* player, const char* entryName);
al::LiveActor* getPlayerHeroEyes(const PlayerActorHakoniwa* player);
al::LiveActor* getPlayerLeftHand(const PlayerActorHakoniwa* player);
al::LiveActor* getPlayerRightHand(const PlayerActorHakoniwa* player);

/**
 * Checks if a player will die in the next frame
 */
bool isPlayerTriggerDeath(const PlayerActorHakoniwa* player);

/**
 * Kills the player with the given death type (defaults to Random)
 * @param playerActor The player to kill
 * @param deathType The type of death to kill the player with. Each type is tied to an animation
 */
void killPlayer(PlayerActorBase* playerActor, PlayerDeathType deathType = PlayerDeathType::Random);

/**
 * Checks if the player currently has a 3D model
 */
bool isPlayer3d(const PlayerActorHakoniwa* player);

/**
 * Initializes a Mario model with the given information
 * @param modelActor The model actor to initialize
 * @param initInfo The info
 * @param costumeBodyName
 * @param capCostumeName
 * @param audioKeeper The player's AudioKeeper
 * @return The info of the costume the player was initialized with
 */
PlayerCostumeInfo* initMarioModelActorNoCloset(al::LiveActor* modelActor, const al::ActorInitInfo& initInfo, const char* costumeBodyName, const char* capCostumeName, al::AudioKeeper* audioKeeper);

/**
 * Initializes a Mario model with ml::initMarioModelActorNoCloset, then registers it in a Player's model holder.
 */
bool initAndRegisterMarioModel(const PlayerActorHakoniwa* player, const char* modelActorEntryName, const al::ActorInitInfo& initInfo, const char* costumeBodyName, const char* capCostumeName);

/**
 * Copies an actor's pose to a player puppet
 */
void copyPoseToPuppet(const al::LiveActor* sourceActor, IUsePlayerPuppet* puppet);

/**
 * Sets the scale of a player and its HackCap
 */
void setPlayerScale(PlayerActorHakoniwa* player, float scale);

/**
 * Emits an effect using the player's current model
 */
void emitPlayerEffect(const PlayerActorHakoniwa* player, const char* effectName);

/**
 * Emits an effect using the player's current model
 */
void emitPlayerEffect(const PlayerActorHakoniwa* player, const char* effectName, const sead::Vector3f* transPtr);

/**
 * Sets the scale of a player's current model's effect
 */
void setPlayerEffectScale(const PlayerActorHakoniwa* player, const char* effectName, const sead::Vector3f& scale);

/**
 * Stops all the effects of a player's current model
 */
void stopPlayerEffectsAll(const PlayerActorHakoniwa* player);

}
