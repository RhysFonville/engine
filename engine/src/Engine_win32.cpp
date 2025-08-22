#include "engine/Engine.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

std::optional<Error> Engine::load_project_library(const std::string& path) noexcept {
	HMODULE handle{};
#ifdef BUILD_DEBUG
	handle = LoadLibraryA((path + "/Debug/project.dll").c_str());
#else
	handle = LoadLibraryA((path + "/Release/project.dll").c_str());
#endif

	if (handle == NULL) return Error{(int)GetLastError(), std::system_category()};
	return std::nullopt;
}

#endif
