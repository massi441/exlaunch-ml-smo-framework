#pragma once

namespace ml {
class ModSystem;
}

/**
 * Forwards the game's sequence and scene lifetime events to the mod system
 */
struct ModSystemHook {
    static void Install();
    static ml::ModSystem* GetSystem();
};
