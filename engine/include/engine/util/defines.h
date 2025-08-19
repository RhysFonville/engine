#pragma once

#define NODISC [[nodiscard]]

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;
using f32 = float;
using f64 = double;

#ifdef _MSC_VER
	#define STATIC_ASSERT static_assert
#elif defined(__clang__) || defined(__GNUC__)
	#define STATIC_ASSERT _Static_assert
#endif

STATIC_ASSERT(sizeof(u8) == 1u, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2u, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4u, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8u, "Expected u64 to be 8 bytes.");
STATIC_ASSERT(sizeof(i8) == 1u, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2u, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4u, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8u, "Expected i64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f32) == 4u, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8u, "Expected f64 to be 8 bytes.");

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define PLATFORM_WINDOWS 1
	#ifndef _WIN64
		#error "64-bit is required on Windows."
	#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	#define PLATFORM_LINUX 1
	#if defined(__ANDROID__)
		#define PLATFORM_ANDROID 1
	#endif
#elif defined(__unix__)
	#define PLATFORM_UNIX 1
	#elif defined(_POSIX_VERSION)
		#define PLATFORM_POSIX 1
	#elif __APPLE__
		#define PLATFORM_APPLE 1
		#include <TargetConditionals.h>
		#if TARGET_IPHONE_SIMULATOR
			#define PLATFORM_IOS 1
			#define PLATFORM_IOS_SIMULATOR 1
		#elif TARGET_OS_IPHONE
			#define PLATFORM_IOS 1
		#elif TARGET_OS_MAC
			#define VK_USE_PLATFORM_MACOS_MVK
		#else
			#error "Unknown Apple platform."
		#endif
#else
	#error "Unknown platform."
#endif

#ifdef PLATFORM_WINDOWS
	#define RENDERER_D3D12
#elif defined(PLATFORM_APPLE)
    #define RENDERER_VULKAN
#endif

#ifdef PLATFORM_WINDOWS
	#define ATTR_USED __declspec(selectany)
#elif defined(PLATFORM_APPLE)
	#define ATTR_USED __attribute__((used))
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef ENGINE_EXPORTS
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#define ENGINE_API
#endif

#if defined(_DEBUG) || !defined(NDEBUG)
	#define BUILD_DEBUG
#else
	#define BUILD_RELEASE
#endif

#define CLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max : value)

#if defined(__clang__) || defined(__gcc__)
	#define DEPRECATED(message) __attribute__((deprecated(message)))
#elif defined(_MSC_VER)
	#define DEPRECATED(message) __declspec(deprecated(message))
#else
	#error "Unsupported compiler. Unable to know how to define deprecations."
#endif

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)
