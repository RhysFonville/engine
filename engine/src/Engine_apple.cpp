#include <dlfcn.h>
#include "engine/Engine.h"

/*void Engine::load_project_library(const std::string& path) noexcept {
	void* handle{};
#ifdef DEBUG
	handle = dlopen((path + "/Debug/libproject.dylib").c_str(), RTLD_NOW);
#else
	handle = dlopen((path + "/Release/libproject.dylib").c_str(), RTLD_NOW);
#endif
}
*/
