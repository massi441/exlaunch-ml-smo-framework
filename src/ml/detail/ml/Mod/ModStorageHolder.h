#pragma once

namespace al {
class AsyncFunctorThread;
}

namespace sead {
class ExpHeap;
}

namespace ml {
class ModStorage;

/**
 * Owns the mod storage for the lifetime of the sequence, along with the thread that saves it in the background
 */
class ModStorageHolder {
public:
    explicit ModStorageHolder(sead::ExpHeap* heap);
    ~ModStorageHolder();

    ModStorage* getModStorage() const { return mStorage; }

    void onSceneInit();
    void onGameSave(const char* fileName) const;
    void onSceneDestroyed() const;
    void requestSave() const;

private:
    sead::ExpHeap* mHeap = nullptr;
    ModStorage* mStorage = nullptr;
    al::AsyncFunctorThread* mSaveThread = nullptr;
    bool mIsFirstBoot = true;

    void waitForSaveThread() const;
    void saveThreadFunc();
};

}
