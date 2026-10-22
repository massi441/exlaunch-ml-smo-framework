#include <exl/lib.hpp>
#include <string>

#ifndef SUBSDK_MODULE_NAME
#error "\"SUBSDK_MODULE_NAME\" must be specified by the current build"
#endif

struct ModuleName {
    u32 unknown;
    u32 name_length;
    char name[sizeof(SUBSDK_MODULE_NAME)] = SUBSDK_MODULE_NAME;
};

constexpr size_t NameLength = std::char_traits<char>::length(SUBSDK_MODULE_NAME);

__attribute__((section(".nx-module-name")))
extern const ModuleName s_ModuleName = { .unknown = 0, .name_length = NameLength, .name = SUBSDK_MODULE_NAME };

__attribute__((section(".bss")))
rtld::ModuleObject __rtld_module_object__;
