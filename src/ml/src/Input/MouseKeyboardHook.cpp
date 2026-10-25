#include <ml/Input/MouseKeyboardHook.h>

#include <exl/hook/trampoline.hpp>
#include <ml/Input/Keyboard.h>
#include <ml/Input/Mouse.h>
#include <System/GameSystem.h>

namespace {

HOOK_DEFINE_TRAMPOLINE(GameSystemMovementHook) {
    static void Callback(GameSystem* thisPtr) {
        Orig(thisPtr);

        ml::Mouse::Instance().update();
        ml::Keyboard::Instance().update();
    }
};

}

void MouseKeyboardHook::Install() {
    nn::hid::InitializeMouse();
    nn::hid::InitializeKeyboard();

    GameSystemMovementHook::InstallAtSymbol("_ZN10GameSystem8movementEv");
}
