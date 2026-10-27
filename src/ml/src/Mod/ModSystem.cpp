#include <ml/Mod/ModSystem.h>

#include <heap/seadExpHeap.h>
#include <heap/seadHeapMgr.h>
#include <Library/Memory/HeapUtil.h>
#include <ml/Core/Memory/MemorySize.h>
#include <ml/Mod/ModStorageHolder.h>
#include <ml/Util/Abort.h>

namespace ml {

namespace {

constexpr size_t SequenceHeapSize = ml::MemorySize::MegaBytes(1);
constexpr size_t DynamicSceneHeapSize = ml::MemorySize::MegaBytes(1);

}

void ModSystem::initialize() {
    mSequenceHeap = sead::ExpHeap::create(SequenceHeapSize, "ModSequenceHeap", al::getSequenceHeap());

    sead::ScopedCurrentHeapSetter heapSetter(mSequenceHeap);
    mStorageHolder = new ModStorageHolder(mSequenceHeap);
}

void ModSystem::finalize() {
    delete mStorageHolder;
    mStorageHolder = nullptr;

    mSequenceHeap->destroy();
    mSequenceHeap = nullptr;
}

void ModSystem::createSceneHeap(sead::Heap* sceneHeap) {
    mDynamicSceneHeap = sead::ExpHeap::create(DynamicSceneHeapSize, "SceneDynamicHeap", sceneHeap);
}

void ModSystem::destroySceneHeap() {
    if (mStorageHolder) {
        mStorageHolder->onSceneDestroyed();
    }

    mDynamicSceneHeap = nullptr;
}

void ModSystem::onSceneInit() const {
    if (mStorageHolder) {
        mStorageHolder->onSceneInit();
    }
}

void ModSystem::onGameSave(const char* fileName) const {
    if (mStorageHolder) {
        mStorageHolder->onGameSave(fileName);
    }
}

ModStorage* ModSystem::getModStorage() const {
    ml::AbortIf(mStorageHolder == nullptr, "ModStorage is null: it was requested before HakoniwaSequence was created.");

    return mStorageHolder->getModStorage();
}

}
