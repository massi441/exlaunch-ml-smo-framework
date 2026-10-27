#pragma once

#include <ml/Export.h>

namespace sead {
class ExpHeap;
}
namespace ml {
class ModStorage;

/**
 * Initializes the runtime of the ml_core mod
 */
class ModRuntime {
public:
    ML_EXPORT static void Initialize();

    ML_EXPORT static ml::ModStorage* GetModStorage();
    ML_EXPORT static sead::ExpHeap* GetModSequenceHeap();
    ML_EXPORT static sead::ExpHeap* GetDynamicSceneHeap();

    /**
     * Increases the size of the model holder by the requested amount, for the next
     * time PlayerActorHakoniwa::initPlayer is called, which internally creates a PlayerModelHolder
     * @param extraCount The amount of *extra* player costumes to allocate for the player.
     */
    ML_EXPORT static void RequestExtraPlayerCostumes(int extraCount);

    /**
     * Requests the game's heap size to grow to about 6GB. Ensure this is called at startup
     */
    ML_EXPORT static void RequestMemoryExpansion();

private:
    inline static bool sInitialized = false;
};

}
