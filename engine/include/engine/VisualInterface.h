#pragma once

#include "Window.h"

class VisualInterface {
public:
	VisualInterface() {}

	std::optional<Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	bool close() const noexcept;

	Window window{};
	// TODO: Renderer renderer{};
	
private:
	bool close_request{};
};
