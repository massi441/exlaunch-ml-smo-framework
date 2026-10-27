#pragma once

#include <ArduinoJson.hpp>
#include <ml/Memory/HeapAllocator.h>

namespace ml {

/**
 * An ArduinoJson::Allocator that allocates on a sead::Heap
 */
class JsonHeapAllocator final : public ArduinoJson::Allocator {
public:
    explicit JsonHeapAllocator(const char* heapName) : mAllocator(heapName) {}

    explicit JsonHeapAllocator(sead::Heap* heap) : mAllocator(heap) {}

    void* allocate(size_t size) override {
        return mAllocator.alloc(size);
    }

    void deallocate(void* ptr) override {
        mAllocator.free(ptr);
    }

    void* reallocate(void* ptr, size_t newSize) override {
        return mAllocator.realloc(ptr, newSize);
    }

private:
    HeapAllocator mAllocator;
};

}
