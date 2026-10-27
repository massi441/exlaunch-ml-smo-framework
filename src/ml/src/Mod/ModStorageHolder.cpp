#include <ml/Mod/ModStorageHolder.h>

#include <heap/seadExpHeap.h>
#include <heap/seadHeapMgr.h>
#include <Library/Thread/AsyncFunctorThread.h>
#include <Library/Thread/FunctorV0M.h>
#include <ml/Core/String/StringUtil.h>
#include <ml/Log/Log.h>
#include <ml/Mod/ModStorage.h>
#include <nn/os.h>

namespace ml {

namespace {

constexpr const char* CommonSaveFileName = "Common.bin";
constexpr u64 SaveThreadPollMilliseconds = 1;

}

ModStorageHolder::ModStorageHolder(sead::ExpHeap* heap) : mHeap(heap) {
    mStorage = new ModStorage(heap);
    mStorage->load();

    mSaveThread = new al::AsyncFunctorThread("ModStorageSaver", al::FunctorV0M(this, &ModStorageHolder::saveThreadFunc), 1, 0x4000, sead::CoreId::cSub1);
}

ModStorageHolder::~ModStorageHolder() {
    this->waitForSaveThread();

    delete mSaveThread;
    delete mStorage;
}

void ModStorageHolder::onSceneInit() {
    if (!mIsFirstBoot && mStorage->getConfig().isReloadBetweenStages) {
        LOG_TRACE("Loading mod storage before scene");
        mStorage->load();
    }

    mIsFirstBoot = false;
}

void ModStorageHolder::onGameSave(const char* fileName) const {
    bool isGameFileSave = !ml::streql(fileName, CommonSaveFileName);
    if (isGameFileSave) {
        LOG_TRACE("Game is saving %s, saving mod storage", fileName);
        this->requestSave();
    }
}

void ModStorageHolder::onSceneDestroyed() const {
    this->waitForSaveThread();

    LOG_TRACE("Scene is being destroyed, saving mod storage");
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);
    mStorage->save();
}

void ModStorageHolder::requestSave() const {
    if (mSaveThread->isDone()) {
        mSaveThread->start();
    }
}

void ModStorageHolder::waitForSaveThread() const {
    while (!mSaveThread->isDone()) {
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(SaveThreadPollMilliseconds));
    }
}

void ModStorageHolder::saveThreadFunc() {
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);
    mStorage->save();
}

}
