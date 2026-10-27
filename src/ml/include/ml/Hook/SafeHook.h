#pragma once

#include <concepts>

namespace ml {

template <typename>
class SafeHook;

template <typename T, typename... Args>
requires std::derived_from<T, SafeHook<T>>
void InstallSafeHook(Args&&... args);

/**
 * A class for creating a hook that can only be installed once. Useful when multiple mods might try to install
 * the same hook but the hook needs to be only installed once.
 */
template <typename>
class SafeHook {
protected:
    SafeHook() {}

    virtual void Install() = 0;

    static bool IsInstalled() {
        return sIsInstalled;
    }

private:
    void SafeInstall() {
        if (sIsInstalled) {
            return;
        }

        this->Install();

        sIsInstalled = true;
    }

private:
    inline static bool sIsInstalled = false;

    template <typename T, typename... Args>
    requires std::derived_from<T, SafeHook<T>>
    friend void InstallSafeHook(Args&&... args);
};

template <typename T, typename... Args>
requires std::derived_from<T, SafeHook<T>>
void InstallSafeHook(Args&&... args) {
    T hook = T(std::forward<Args>(args)...);

    hook.SafeInstall();
}

}
