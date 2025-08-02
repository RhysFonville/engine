#include <engine/Window.h>
#include <chrono>
#include <thread>

void sleep(Window& window) {
    window.process_events();
    std::this_thread::sleep_for(std::chrono::seconds{3});
}

int main() {
    log("Creating");
	Window window{};
    if (auto err{window.init()})  {log(LogLevel::ERROR, err.value()); return EXIT_FAILURE; }
    sleep(window);

    log("Hiding");
    window.hide();
    sleep(window);

    log("Showing");
    window.show();
    sleep(window);

    log("Maximizing");
    window.maximize();
    sleep(window);

    log("Restoring");
    window.restore();
    sleep(window);

    log("Setting size (+50)");
    window.set_size(window.get_size()+50);
    sleep(window);

    log("Setting position (+50)");
    window.set_position(window.get_position()+50);
    sleep(window);

    log("Minimizing");
    window.minimize();
    sleep(window);

    log("Restoring, check your taskbar, requesting attention next");
    window.restore();
    sleep(window);

    log("Requesting attention, unfocus window, focusing next");
    window.request_attention();
    sleep(window);
    
    log("Focusing");
    window.focus();
    sleep(window);

    log("Setting title");
    window.set_title("Test window");
    sleep(window);

    log("Seeting size limits");
    window.set_size_limits(Vector2{200, 200}, Vector2{800, 800});
    sleep(window);

    log("Setting opacity");
    window.set_opacity(window.get_opacity()-.5f);
    sleep(window);

    log("Processing events");
	while (window.process_events()) { }

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif
