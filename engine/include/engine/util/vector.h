#pragma once

#include <type_traits>
#include "defines.h"

template<class T> concept numeric = std::is_arithmetic_v<T>;

template <numeric T>
struct TVector2 {
    T x{}, y{};

    TVector2 operator+(T x) { return TVector2{this->x+x, y+x}; }
    TVector2 operator-(T x) { return TVector2{this->x-x, y-x}; }
    TVector2 operator*(T x) { return TVector2{this->x*x, y*x}; }
    TVector2 operator/(T x) { return TVector2{this->x/x, y/x}; }
};

using Vector2 = TVector2<i32>;
using FVector2 = TVector2<f32>;

