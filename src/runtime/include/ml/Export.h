#pragma once

/**
 * This file contains macros for defining exportable symbols of the ml framework
 */

#ifdef ML_DYNAMIC_RUNTIME
#define ML_EXPORT __attribute__((visibility("default")))
#define ML_EXPORT_SCOPE_BEGIN _Pragma("GCC visibility push(default)")
#define ML_EXPORT_SCOPE_END _Pragma("GCC visibility pop")
#else
#define ML_EXPORT
#define ML_EXPORT_SCOPE_BEGIN
#define ML_EXPORT_SCOPE_END
#endif

