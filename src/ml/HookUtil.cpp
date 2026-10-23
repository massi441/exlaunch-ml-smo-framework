#include <ml/Hook/HookUtil.h>

#include <nn/ro.h>

namespace ml {

bool lookUpSymbol(uintptr_t* outAddress, const char* symbol) {
    nn::Result result = nn::ro::LookupSymbol(outAddress, symbol);

    return result.IsSuccess();
}

bool isExistSymbol(const char* symbol) {
    uintptr_t address;

    return ml::lookUpSymbol(&address, symbol);
}

}
