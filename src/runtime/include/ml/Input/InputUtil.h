#pragma once

#include <math/seadVector.hpp>
#include <ml/Input/InputTypes.h>

namespace ml {

bool isKeyClicked(ml::KeyboardKey key);
bool isKeyReleased(ml::KeyboardKey key);
bool isKeyDown(ml::KeyboardKey key);

bool isButtonClicked(ml::MouseButton button);
bool isButtonReleased(ml::MouseButton button);
bool isButtonDown(ml::MouseButton button);

sead::Vector2f getMousePos();

}
