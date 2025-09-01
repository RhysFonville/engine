#include "engine/Engine.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

std::optional<Error> Engine::load_project_library(const std::string& path) noexcept {
	std::string lib_path{path + "/"};
#ifdef BUILD_DEBUG
	lib_path += "Debug";
#else
	lib_path += "Release";
#endif
	lib_path += "/project.dll";

	if (std::filesystem::exists(lib_path)) {
		HMODULE handle{};
		handle = LoadLibraryA((lib_path + "/Release/project.dll").c_str());
		if (handle == NULL) return MK_ERROR((int)GetLastError(), std::system_category());
	}
	return std::nullopt;
}

#endif
