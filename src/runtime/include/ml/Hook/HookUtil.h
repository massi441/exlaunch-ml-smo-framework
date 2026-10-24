#pragma once

#include <cstdlib>
#include <exl/hook/base.hpp>

#define ASSERT_STATIC_CALLBACK(CallbackFuncType) static_assert(!std::is_member_function_pointer_v<CallbackFuncType>, "Callback method must be static!");

namespace ml {

bool lookUpSymbol(uintptr_t* outAddress, const char* symbol);
bool isExistSymbol(const char* symbol);

inline uint64_t getBaseAddress() {
    return reinterpret_cast<uint64_t>(malloc) - 0x00724b94;
}

inline uint64_t getAddressOffset(uint64_t address) {
    return address - getBaseAddress();
}

inline uint64_t getAddressOffset(void* ptr) {
    return getAddressOffset(reinterpret_cast<uint64_t>(ptr));
}

/**
 * Returns the actual runtime address of a variable, from an offset found in the binary.
 * @param offset The offset of the variable in the binary
 * @return The runtime address of the offset
 */
inline uint64_t getRuntimeAddress(uint64_t offset) {
    return offset + getBaseAddress();
}

template <typename T>
const void* getVTablePtr(const T* ptr) {
    return *reinterpret_cast<const T* const*>(ptr);
}

/**
 * Returns a pointer to an object found at an offset in the binary.
 * @tparam T The type of object
 * @param offset The offset of the object in the binary
 * @return A pointer to the
 */
template <typename T>
T getRuntimePtr(uint64_t offset) {
    return reinterpret_cast<T>(getRuntimeAddress(offset));
}

template <typename T>
T* reinterpretMemberAsPtr(const void* ptr, uint memberOffset) {
    return reinterpret_cast<T*>(reinterpret_cast<uint64_t>(ptr) + memberOffset);
}

template <typename T>
T& reinterpretMemberAsRef(const void* ptr, uint memberOffset) {
    return *reinterpret_cast<T*>(reinterpret_cast<uint64_t>(ptr) + memberOffset);
}

template <typename T>
T reinterpretMember(const void* ptr, uint memberOffset) {
    return *reinterpret_cast<T*>(reinterpret_cast<uint64_t>(ptr) + memberOffset);
}

template <typename T>
void setMember(void* ptr, uint memberOffset, T value) {
    *reinterpret_cast<T*>(reinterpret_cast<uint64_t>(ptr) + memberOffset) = value;
}

template <typename T>
T as(exl::hook::nx64::impl::GpRegisterAccessor64& xAccessor, int regNum) {
    return reinterpret_cast<T>(xAccessor[regNum]);
}

template <typename T>
T as(exl::hook::nx64::impl::GpRegisterAccessor32& wAccessor, int regNum) {
    return reinterpret_cast<T>(wAccessor[regNum]);
}

template <typename T>
void setAs(exl::hook::nx64::impl::GpRegisterAccessor64& xAccessor, int regNum, T&& value) {
    xAccessor[regNum] = reinterpret_cast<uint64_t>(std::forward<T>(value));
}

template <typename T>
void setAs(exl::hook::nx64::impl::GpRegisterAccessor32& wAccessor, int regNum, T&& value) {
    wAccessor[regNum] = reinterpret_cast<uint64_t>(std::forward<T>(value));
}

}
