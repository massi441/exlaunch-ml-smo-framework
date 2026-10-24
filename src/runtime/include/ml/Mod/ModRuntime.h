#pragma once

#include <ml/Export.h>

namespace ml {

/**
 * Initializes the runtime of the ml_core mod
 */
struct ModRuntime {
    ML_EXPORT static void Initialize();
};

}
