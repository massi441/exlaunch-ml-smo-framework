#pragma once

#include <ml/Hook/SafeHook.h>

class HeapSizeHook : public ml::SafeHook<HeapSizeHook> {
    void Install() override;
};