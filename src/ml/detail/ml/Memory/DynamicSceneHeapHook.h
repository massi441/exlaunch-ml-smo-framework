#pragma once

namespace sead {
class ExpHeap;
}

/**
 * Registers an explicit heap on the scene heap, such that dynamic memory allocations can be freed on the scene heap
 */
struct DynamicSceneHeapHook {
    static void Install();
    static sead::ExpHeap* GetHeap();
};
