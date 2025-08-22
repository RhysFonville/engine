#include <dlfcn.h>
#include "engine/Engine.h"
#include "engine/util/defines.h"

#ifdef PLATFORM_APPLE

std::optional<Error> Engine::load_project_library(const std::string& path) noexcept {
	void* handle{};
#ifdef BUILD_DEBUG
	handle = dlopen((path + "/Debug/libproject.dylib").c_str(), RTLD_NOW);
#else
	handle = dlopen((path + "/Release/libproject.dylib").c_str(), RTLD_NOW);
#endif

	if (handle == nullptr) return Error{1, engine_category()};
	return std::nullopt;
}

#endif

