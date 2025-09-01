#include <dlfcn.h>
#include "engine/Engine.h"
#include "engine/util/defines.h"

#ifdef PLATFORM_APPLE

std::optional<Error> Engine::load_project_library(const std::string& path) noexcept {
	std::string lib_path{path + "/"};
#ifdef BUILD_DEBUG
	lib_path += "Debug";
#else
	lib_path += "Release";
#endif
	lib_path += "/libproject.dylib";

	if (std::filesystem::exists(lib_path)) {
		void* handle{};
		handle = dlopen(lib_path.c_str(), RTLD_NOW);
		if (handle == nullptr) return MK_ERROR(1, engine_category());
	}
	return std::nullopt;
}

#endif

