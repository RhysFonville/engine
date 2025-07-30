#pragma once

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

#if defined(__clang__) || defined(__GNUC__)
	#define STATIC_ASSERT _Static_assert
#else
	#define STATIC_ASSERT static_assert
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
	#define KPLATFORM_WINDOWS 1
	#ifndef _WIN64
		#error "64-bit is required on Windows."
	#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	#define KPLATFORM_LINUX 1
	#if defined(__ANDROID__)
		#define KPLATFORM_ANDROID 1
	#endif
#elif defined(__unix__)
	#define KPLATFORM_UNIX 1
	#elif defined(_POSIX_VERSION)
		#define KPLATFORM_POSIX 1
	#elif __APPLE__
		#define KPLATFORM_APPLE 1
		#include <TargetConditionals.h>
		#if TARGET_IPHONE_SIMULATOR
			#define KPLATFORM_IOS 1
			#define KPLATFORM_IOS_SIMULATOR 1
		#elif TARGET_OS_IPHONE
			#define KPLATFORM_IOS 1
		#elif TARGET_OS_MAC
			#define VK_USE_PLATFORM_MACOS_MVK
		#else
			#error "Unknown Apple platform."
		#endif
#else
	#error "Unknown platform."
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

#if _DEBUG
	#define DEBUG 1
	#define RELEASE 0
#else
	#define RELEASE 1
	#define DEBUG 0
#endif

#define CLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max : value)

#if defined(__clang__) || defined(__gcc__)
#define DEPRECATED(message) __attribute__((deprecated(message)))
#elif defined(_MSC_VER)
#define DEPRECATED(message) __declspec(deprecated(message))
#else
#error "Unsupported compiler. Can't know how to define deprecations!"
#endif

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)
