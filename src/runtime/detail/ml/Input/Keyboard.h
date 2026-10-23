#pragma once

#include <nn/hid.h>

#include "Core/Util/Macros.h"
#include "CoreMod/Input/InputTypes.h"

namespace ml {

class Keyboard {
    NO_COPY_NO_MOVE(Keyboard)
public:
    static Keyboard& Instance() {
        static Keyboard instance;
        return instance;
    }

    void update();

    bool isKeyClicked(ml::KeyboardKey key) const;
    bool isKeyReleased(ml::KeyboardKey key) const;
    bool isKeyDown(ml::KeyboardKey key) const;

private:
    ml::KeyboardState mPreviousState;
    ml::KeyboardState mCurrentState;

    Keyboard();
};

}
