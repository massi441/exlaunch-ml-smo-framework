 #include <cstdint>
#include <exl/nx/types.h>

namespace exl::reloc {
    /* Bound to the SDK's nn::ro::LookupSymbol, without redeclaring it, so it doesn't clash with the SDK's nn/ro.h */
    ::Result LookupSymbol(uintptr_t *out, const char *name) asm("_ZN2nn2ro12LookupSymbolEPmPKc");
}
