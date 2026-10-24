#pragma once

#include <ml/Export.h>

ML_EXPORT_SCOPE_BEGIN

namespace ml {

[[noreturn]] void Abort(const char* fmt, ...);

void AbortIf(bool condition, const char* fmt, ...);
void AbortIfNot(bool condition, const char* fmt, ...);

}

ML_EXPORT_SCOPE_END
