#pragma once

#include <Library/Thread/FunctorV0M.h>
#include <ml/CoreSMO/Misc/ActorConcepts.h>

namespace ml {

template <typename F>
class FunctorV0 : public al::FunctorBase {
public:
    FunctorV0() = default;
    FunctorV0(F functPointer) : mFuncPointer(functPointer) {}

    void operator()() const override { mFuncPointer(); }

    FunctorV0* clone() const override { return new FunctorV0(*this); }

private:
    F mFuncPointer;
};

}

template <LiveActorType T, typename R = void>
using LiveActorFunctor = al::FunctorV0M<T*, LiveActorFunc<T, R>>;

template <LiveActorType T, typename R = void>
using LiveActorFunctorConst = al::FunctorV0M<T*, LiveActorConstFunc<T, R>>;
