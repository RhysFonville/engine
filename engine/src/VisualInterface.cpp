#include "engine/VisualInterface.h"

std::expected<VisualInterface, Error> VisualInterface::init() noexcept {
	auto window{Window::init()};
	if (!window.has_value()) return std::unexpected{window.error()};
	return VisualInterface{std::move(*window)};
}

void VisualInterface::tick() noexcept {
	close_request = !window.process_events();
}

void VisualInterface::clean_up() noexcept {
	window.clean_up();
}

bool VisualInterface::close() const noexcept {
	return close_request;
}

