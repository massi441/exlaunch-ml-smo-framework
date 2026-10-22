#include "patcher_impl.hpp"

#include <exl/util/sys/mem_layout.hpp>

// from massi: extern var storage and functions using it is added here so other subsdk's don't keep local copies of them

namespace exl::patch::impl {

util::TypedStorage<const util::RwPages> s_Storage;

const util::RwPages& GetRwPages() { return util::GetReference(s_Storage); }

void InitPatcherImpl() {
    auto& mod = util::GetMainModuleInfo();
    auto start = mod.m_Total.m_Start;
    auto size = mod.m_Rodata.GetEnd() - start;
    util::ConstructAt(s_Storage, start, size);
}

}