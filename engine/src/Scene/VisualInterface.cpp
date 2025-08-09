#include "engine/Scene/VisualInterface.h"

std::optional<Error> VisualInterface::init() noexcept {
	return window.init();
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

