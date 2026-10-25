#pragma once

#include <ml/Core/Util/Enum.h>

namespace ml {

DATA_ENUM(
    LogLevel,
    Verbose,
    Trace,
    Debug,
    Information,
    Warning,
    Error,
    Critical,
    Fatal,
);

}
