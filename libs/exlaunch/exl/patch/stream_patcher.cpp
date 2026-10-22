#include "stream_patcher.hpp"

// from massi: implementations of the patcher are in this translation unit so other
// subsdk's do not need to recompile the code patcher (since it was inline before)

namespace exl::patch {

StreamPatcher::StreamPatcher(uintptr_t start) : m_Start(start), m_Current(start) {

}

void StreamPatcher::Flush() {
    /* Nothing to flush if there was nothing done. */
    if(DoneNothing())
        return;

    /* Get actual pointers. */
    void* ro = reinterpret_cast<void*>(RoFromAddr(m_Start));
    void* rw = reinterpret_cast<void*>(RwFromAddr(m_Start));
    auto size = m_Current - m_Start;

    /* Flush data/instructions. */
    armDCacheFlush(rw, size);
    armICacheInvalidate(ro, size);

    /* Reset start position. */
    m_Start += size;
}

void StreamPatcher::SeekRel(uintptr_t address) {
    /* Don't need to do anything if the address doesn't need to change. */
    if(address == 0)
        return;

    /* Get address relative to base. */
    address += m_Current;

    /* Flush what we've already done. */
    Flush();

    /* Reset to the position to the provided address. */
    m_Start = address;
    m_Current = address;
}

void StreamPatcher::Seek(uintptr_t address)  {
    SeekRel(RelativeAddressFromBase(address));
}

void StreamPatcher::Seek(void* ptr) {
    SeekRel(RelativeAddressFromPointer(ptr));
}

StreamPatcher::~StreamPatcher() {
    Flush();
}

}
