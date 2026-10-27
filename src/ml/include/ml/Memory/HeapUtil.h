#pragma once

#include <cstddef>
#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>
#include <ml/Log/Log.h>

namespace ml {

inline sead::Heap* findHeap(const char* heapName, int occurrence = 0) {
    sead::HeapMgr* heapMgr = sead::HeapMgr::instance();

    if (heapMgr == nullptr) {
        LOG_WARNING("Tried to find %s heap, but the heap manager was null", heapName);
        return nullptr;
    }

    return heapMgr->findHeapByName(heapName, occurrence);
}

inline sead::Heap* findSceneHeap() {
    return ml::findHeap("SceneHeap");
}

inline sead::Heap* findStationedHeap() {
    return ml::findHeap("StationedHeap");
}

inline sead::Heap* getCurrentHeap() {
    return sead::HeapMgr::instance()->getCurrentHeap();
}

inline const char* getCurrentHeapName() {
    return ml::getCurrentHeap()->getName().cstr();
}

inline size_t getCurrentHeapFreeSize() {
    sead::HeapMgr* heapMgr = sead::HeapMgr::instance();
    if (heapMgr == nullptr) {
        return 0;
    }

    sead::Heap* heap = heapMgr->getCurrentHeap();
    if (heap == nullptr) {
        return 0;
    }

    return heap->getFreeSize();
}

}
