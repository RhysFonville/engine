#include <engine/Window.h>
#include <engine/Input/InputSet.h>

#undef ERROR

int main() {
    Window window{};
    window.init();

    InputSet set{};
    set.set_keybinds({
        Keybind{Key::A, KeyEvent::Down, [&]() -> void {
            log(LogLevel::INFO, "A is pressed.");
        }},
        Keybind{Key::A, KeyEvent::Up, [&]() -> void {
            log(LogLevel::INFO, "A is released.");
        }},
        Keybind{Key::A, KeyEvent::CurrentlyDown, [&]() -> void {
            log(LogLevel::INFO, "A is held.");
        }}
    });

    while (window.process_events()) { }

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif
