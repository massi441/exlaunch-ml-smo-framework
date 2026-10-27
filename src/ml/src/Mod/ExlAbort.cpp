#include <exl/hook/nx64/impl.hpp>
#include <ml/Log/DebugPrint.h>

namespace exl::diag {
void WEAK NORETURN NOINLINE AbortImpl(const AbortCtx& ctx) {
    ml::svcPrint("EXL ABORT");

    if (ctx.format) {
        ml::svcPrintFmtV(ctx.format, ctx.args);
    }

    svcBreak(ctx.isAssertion ? BreakReason_Assert : BreakReason_Panic, ctx.value, 0);

    UNREACHABLE;
}

}