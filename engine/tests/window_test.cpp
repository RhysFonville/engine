#include <cstdlib>
#include <engine/Window.h>

int main() {
    Window window{};
    if (auto err{window.init()})  {log(LogLevel::ERROR, err.value()); return EXIT_FAILURE; }

    window.hide();
    window.show();

    window.minimize();
    window.restore();

    window.maximize();

    window.request_attention();

    window.focus();
    
    window.set_title("Test window");

    window.set_position(window.get_position()+50);
    window.set_size(window.get_size()+50);
    window.set_size_limits(Vector2{200, 200}, Vector2{1000, 10000});

    window.set_opacity(window.get_opacity()-.5f);

    window.process_events();

    return EXIT_SUCCESS;
}

