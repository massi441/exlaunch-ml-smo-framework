#include <ml/Network/Network.h>

#include <exl/lib.hpp>
#include <ml/Log/Log.h>
#include <ml/Util/Abort.h>
#include <nn/nifm.h>
#include <nn/socket.hpp>

namespace ml {

namespace {

constexpr size_t SocketPoolSize = 0x200000; // 2MB
char SocketPool[SocketPoolSize] __attribute__((aligned(PAGE_SIZE)));
constexpr size_t SocketPoolAllocationSize = 0x20000; // 128KB
constexpr int SocketConcurrentLimit = 12;

}

void Network::Initialize() {
    nn::Result networkResult = nn::nifm::Initialize();
    if (networkResult.IsFailure()) {
        LOG_ERROR("Error: Failed to initialize nifm: %d", networkResult.GetDescription());
        return;
    }

    nn::Result poolResult = nn::socket::Initialize(SocketPool, SocketPoolSize, SocketPoolAllocationSize, SocketConcurrentLimit);
    if (poolResult.IsFailure()) {
        LOG_ERROR("Error: Failed to initialize socket pool: %d", poolResult.GetDescription());
        return;
    }

    // future socket initialization calls return nn::Result::Success() early
    exl::util::RwPages pages(reinterpret_cast<uintptr_t>(&nn::socket::Initialize), 2 * sizeof(u32)); // we need to patch 2 instructions
    u32* instructions = pages.GetRw<u32>();
    instructions[0] = exl::armv8::inst::Movz(exl::armv8::reg::W0, 0).Value(); // mov w0, #0 --> 0 means success for nn::Result
    instructions[1] = exl::armv8::inst::Ret().Value(); // ret

    LOG_INFORMATION("Socket pool initialized");

    nn::nifm::SubmitNetworkRequestAndWait();

    if (!nn::nifm::IsNetworkAvailable()) {
        LOG_ERROR("Network is not available");
        return;
    }

    LOG_DEBUG("Network successfully initialized");
}

}
