#include <engine/Window.h>

int main() {
	Window window{};
	window.init();

	while (true) {
		//if (!window.process_events()) break;
	}

	return EXIT_SUCCESS;
}
