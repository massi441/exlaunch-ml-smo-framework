#include <ml/Input/Mouse.h>

namespace ml {

static bool TestButton(const ml::MouseState& state, ml::MouseButton button) {
    return state.mButtons.Test(static_cast<int>(button));
}

Mouse::Mouse() : mPreviousState(), mCurrentState() {

}

void Mouse::update() {
    mPreviousState = mCurrentState;
    nn::hid::GetMouseState(&mCurrentState);
}

float Mouse::getX() const {
    return mCurrentState.mX;
}

float Mouse::getY() const {
    return mCurrentState.mY;
}

bool Mouse::isButtonClicked(ml::MouseButton button) const {
    return !TestButton(mPreviousState, button) && TestButton(mCurrentState, button);
}

bool Mouse::isButtonReleased(ml::MouseButton button) const {
    return TestButton(mPreviousState, button) && !TestButton(mCurrentState, button);
}

bool Mouse::isButtonDown(ml::MouseButton button) const {
    return TestButton(mPreviousState, button) && TestButton(mCurrentState, button);
}

}
