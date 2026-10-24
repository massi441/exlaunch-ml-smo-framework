#pragma once

#include <ml/Core/Util/Macros.h>
#include <ml/Input/InputTypes.h>

namespace ml {

class Mouse {
    NO_COPY_NO_MOVE(Mouse)
public:
    static Mouse& Instance() {
        static Mouse instance;
        return instance;
    }

    void update();

    float getX() const;
    float getY() const;

    bool isButtonClicked(ml::MouseButton button) const;
    bool isButtonReleased(ml::MouseButton button) const;
    bool isButtonDown(ml::MouseButton button) const;

private:
    ml::MouseState mPreviousState;
    ml::MouseState mCurrentState;

    Mouse();
};

}
