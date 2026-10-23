#include <ml/Input/InputUtil.h>

#include <ml/Input/Keyboard.h>
#include <ml/Input/Mouse.h>

namespace ml {

bool isKeyClicked(ml::KeyboardKey key) {
    return ml::Keyboard::Instance().isKeyClicked(key);
}

bool isKeyReleased(ml::KeyboardKey key) {
    return ml::Keyboard::Instance().isKeyReleased(key);
}

bool isKeyDown(ml::KeyboardKey key) {
    return ml::Keyboard::Instance().isKeyDown(key);
}

bool isButtonReleased(ml::MouseButton button) {
    return ml::Mouse::Instance().isButtonReleased(button);
}

bool isButtonDown(ml::MouseButton button) {
    return ml::Mouse::Instance().isButtonDown(button);
}

float getMouseX() {
    return ml::Mouse::Instance().getX();
}

float getMouseY() {
    return ml::Mouse::Instance().getY();
}

sead::Vector2f getMousePos() {
    const ml::Mouse& mouse = ml::Mouse::Instance();
    return sead::Vector2f(mouse.getX(), mouse.getY());
}

}
