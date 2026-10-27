#pragma once

#include <concepts>

#include <Library/LiveActor/LiveActor.h>

template <typename T>
concept LiveActorType = std::derived_from<T, al::LiveActor>;

template <LiveActorType T, typename R = void>
using LiveActorFunc = R (T::*)();

template <LiveActorType T, typename R = void>
using LiveActorConstFunc = R (T::*)() const;
