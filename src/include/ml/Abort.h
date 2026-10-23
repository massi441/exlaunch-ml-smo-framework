#pragma once

namespace ml {

[[noreturn]] void Abort(const char* fmt, ...);

void AbortIf(bool condition, const char* fmt, ...);
void AbortIfNot(bool condition, const char* fmt, ...);

}
