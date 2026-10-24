#include <exl/lib.hpp>
#include <string>

#ifndef ML_SUBSDK_MODULE_NAME
#error "\"ML_SUBSDK_MODULE_NAME\" must be specified by the current build"
#endif

struct ModuleName {
    u32 unknown;
    u32 name_length;
    char name[sizeof(ML_SUBSDK_MODULE_NAME)] = ML_SUBSDK_MODULE_NAME;
};

constexpr size_t NameLength = std::char_traits<char>::length(ML_SUBSDK_MODULE_NAME);

__attribute__((section(".nx-module-name")))
extern const ModuleName s_ModuleName = { .unknown = 0, .name_length = NameLength, .name = ML_SUBSDK_MODULE_NAME };

__attribute__((section(".bss")))
rtld::ModuleObject __rtld_module_object__;
