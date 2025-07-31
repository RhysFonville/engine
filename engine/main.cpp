#include <engine/Window.h>

int main() {
	Window window{};
	window.init();

	while (true) {
		if (!window.process_events()) break;
	}

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif
