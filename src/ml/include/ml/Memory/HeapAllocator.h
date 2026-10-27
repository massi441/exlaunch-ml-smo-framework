#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <ml/Memory/HeapUtil.h>
#include <ml/Util/Abort.h>

namespace ml {

class HeapAllocator {
public:
    explicit HeapAllocator(const char* heapName) {
        mHeap = ml::findHeap(heapName);

        ml::AbortIf(mHeap == nullptr, "Heap %s doesn't exist, HeapAllocator cannot be created", heapName);
    }

    explicit HeapAllocator(sead::Heap* heap) {
        ml::AbortIf(heap == nullptr, "Tried to pass a null heap to a HeapAllocator");

        mHeap = heap;
    }

    void* alloc(size_t size, s32 alignment = sizeof(void*)) const {
        return mHeap->tryAlloc(size, alignment);
    }

    void free(void* ptr) const {
        mHeap->free(ptr);
    }

    void* realloc(void* ptr, size_t size, s32 alignment = sizeof(void*)) const {
        return mHeap->tryRealloc(ptr, size, alignment);
    }

private:
    sead::Heap* mHeap;
};

}
