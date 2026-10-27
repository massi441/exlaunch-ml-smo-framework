#include <ml/Mod/ModUtil.h>

#include <ml/Mod/ModSystem.h>
#include <ml/Mod/ModSystemHook.h>

namespace ml {

ModStorage* getModStorage() {
    return ModSystemHook::GetSystem()->getModStorage();
}

sead::ExpHeap* getDynamicSceneHeap() {
    return ModSystemHook::GetSystem()->getDynamicSceneHeap();
}

sead::ExpHeap* getModSequenceHeap() {
    return ModSystemHook::GetSystem()->getSequenceHeap();
}

}
