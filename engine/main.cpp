#include <engine/Window.h>

int main() {
	Window window{};
	window.init();

	while (true) {
        auto b{window.process_events()};
        if (!b.has_value()) { log(LogLevel::ERROR, b.error()); return EXIT_FAILURE; }
        else if (!b.value()) { break; }
	}

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif
