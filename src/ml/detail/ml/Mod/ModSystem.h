#pragma once

namespace sead {
class ExpHeap;
class Heap;
}

namespace ml {
class ModStorage;
class ModStorageHolder;

/**
 * Owns the mod resources that follow the game's sequence and scene lifetimes, and creates
 * and destroys them in a fixed order
 */
class ModSystem {
public:
    ModSystem() = default;

    void initialize();
    void finalize();
    void createSceneHeap(sead::Heap* sceneHeap);
    void destroySceneHeap();
    void onSceneInit() const;
    void onGameSave(const char* fileName) const;

    sead::ExpHeap* getSequenceHeap() const { return mSequenceHeap; }
    sead::ExpHeap* getDynamicSceneHeap() const { return mDynamicSceneHeap; }
    ModStorage* getModStorage() const;

private:
    sead::ExpHeap* mSequenceHeap = nullptr;
    sead::ExpHeap* mDynamicSceneHeap = nullptr;
    ModStorageHolder* mStorageHolder = nullptr;
};

}
