#pragma once

#include <type_traits>
#include "defines.h"

template<typename T> concept numeric = std::is_arithmetic_v<T>;

template <numeric T>
struct TVector2 {
    T x{}, y{};

	template <numeric U>
    TVector2 operator+(const TVector2<U>& v) { return TVector2{x+v.x, y+v.y}; }
	template <numeric U>
    TVector2 operator-(const TVector2<U>& v) { return TVector2{x-v.x, y-v.y}; }
	template <numeric U>
    TVector2 operator*(const TVector2<U>& v) { return TVector2{x*v.x, y*v.y}; }
	template <numeric U>
    TVector2 operator/(const TVector2<U>& v) { return TVector2{x/v.x, y/v.y}; }

    TVector2 operator+(numeric auto n) { return TVector2{x+n, y+n}; }
    TVector2 operator-(numeric auto n) { return TVector2{x-n, y-n}; }
    TVector2 operator*(numeric auto n) { return TVector2{x*n, y*n}; }
    TVector2 operator/(numeric auto n) { return TVector2{x/n, y/n}; }
};

template <numeric T>
struct TVector3 {
    T x{}, y{}, z{};

	template <numeric U>
    TVector3 operator+(const TVector2<U>& v) { return TVector3{x+v.x, y+v.y, z}; }
	template <numeric U>
    TVector3 operator-(const TVector2<U>& v) { return TVector3{x-v.x, y-v.y, z}; }
	template <numeric U>
    TVector3 operator*(const TVector2<U>& v) { return TVector3{x*v.x, y*v.y, z}; }
	template <numeric U>
    TVector3 operator/(const TVector2<U>& v) { return TVector3{x/v.x, y/v.y, z}; }

	template <numeric U>
    TVector3 operator+(const TVector3<U>& v) { return TVector3{x+v.x, y+v.y, z+v.z}; }
	template <numeric U>
    TVector3 operator-(const TVector3<U>& v) { return TVector3{x-v.x, y-v.y, z-v.z}; }
	template <numeric U>
    TVector3 operator*(const TVector3<U>& v) { return TVector3{x*v.x, y*v.y, z*v.z}; }
	template <numeric U>
    TVector3 operator/(const TVector3<U>& v) { return TVector3{x/v.x, y/v.y, z/v.z}; }

    TVector3 operator+(numeric auto n) { return TVector3{x+n, y+n, z+n}; }
    TVector3 operator-(numeric auto n) { return TVector3{x-n, y-n, z-n}; }
    TVector3 operator*(numeric auto n) { return TVector3{x*n, y*n, z*n}; }
    TVector3 operator/(numeric auto n) { return TVector3{x/n, y/n, z/n}; }
};

using Vector2 = TVector2<i32>;
using FVector2 = TVector2<f32>;
using Vector3 = TVector3<i32>;
using FVector3 = TVector3<f32>;

struct ENGINE_API Transform {
	FVector3 position{}, rotation{}, size{};
	
	void transform(auto n) noexcept { position += n; }
	void rotate(auto n) noexcept { rotation += n; }
	void scale(auto n) noexcept { size += n; }
};

