#include "engine/Window.h"

struct Window::Impl { };

Window::Window() noexcept { }

std::optional<Error> Window::init() noexcept {
	return std::nullopt;
}

bool Window::process_events() noexcept {
	return false;
}
