#include "CoreMod/Input/Keyboard.h"

#include <ml/Util/Logger.h>

namespace ml {

static bool TestKey(const ml::KeyboardState& state, ml::KeyboardKey key) {
    return state.mKeys.Test(static_cast<int>(key));
}

Keyboard::Keyboard() : mPreviousState(), mCurrentState() {

}

void Keyboard::update() {
    mPreviousState = mCurrentState;
    nn::hid::GetKeyboardState(&mCurrentState);
}

bool Keyboard::isKeyClicked(ml::KeyboardKey key) const {
    return !TestKey(mPreviousState, key) && TestKey(mCurrentState, key);
}

bool Keyboard::isKeyReleased(ml::KeyboardKey key) const {
    return TestKey(mPreviousState, key) && !TestKey(mCurrentState, key);
}

bool Keyboard::isKeyDown(ml::KeyboardKey key) const {
    return TestKey(mPreviousState, key) && TestKey(mCurrentState, key);
}

}
