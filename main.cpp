#include <chrono>
#include <thread>
#include <engine/AssetManager/AssetManager.h>

#undef ERROR

int main() {
	AssetManager am{};

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif
