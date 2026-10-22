#pragma once

#include <exl/util/sys/rw_pages.hpp>
#include <exl/util/typed_storage.hpp>

namespace exl::patch {

    namespace impl {
        extern util::TypedStorage<const util::RwPages> s_Storage;

        const util::RwPages& GetRwPages();

        void InitPatcherImpl();
    };

    class PatcherImpl {
    protected:
        const util::RwPages& m_Pages;

        template<typename T>
        T& At(const uintptr_t offset) {
            /* Get address for the object. */
            uintptr_t start = RwFromAddr(offset);

            auto ptr = reinterpret_cast<T*>(start);
            return *ptr;
        }

    public:
        PatcherImpl() : m_Pages(impl::GetRwPages()) {}

        uintptr_t AddrFromRo(uintptr_t ro) const { return ro - m_Pages.GetRo(); }
        uintptr_t AddrFromRw(uintptr_t rw) const { return rw - m_Pages.GetRw(); }

        uintptr_t RoFromAddr(uintptr_t addr) const { return m_Pages.GetRo() + addr; }
        uintptr_t RwFromAddr(uintptr_t addr) const { return m_Pages.GetRw() + addr; }

        ptrdiff_t AddrFromRoPointer(void* ptr) const { return AddrFromRo(reinterpret_cast<uintptr_t>(ptr)); }
        ptrdiff_t AddrFromRwPointer(void* ptr) const { return AddrFromRw(reinterpret_cast<uintptr_t>(ptr)); }
    };
}
