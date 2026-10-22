#pragma once

#include "patcher_impl.hpp"

namespace exl::patch {
    
    class StreamPatcher : public PatcherImpl {
    private:
        constexpr bool DoneNothing() const {
            return m_Start == m_Current;
        }

        void Flush();

    protected:
        ptrdiff_t RelativeAddressFromBase(uintptr_t address) const {
            return address - m_Current;
        }

        ptrdiff_t RelativeAddressFromPointer(void* ptr) const {
            return AddrFromRoPointer(ptr) - m_Current;
        }
        
        uintptr_t m_Start;
        uintptr_t m_Current;

    public:
        StreamPatcher(uintptr_t start);

        template<typename T>
        void Write(T v) {
            At<T>(m_Current) = v;

            m_Current += sizeof(T);
        }

        /* Flush current data then move to a new address. */
        void SeekRel(uintptr_t address);

        /* Address relative to the base (Ro). */
        void Seek(uintptr_t address);

        /* Absolute address. */
        void Seek(void* ptr);

        ~StreamPatcher();
    };
}
