#pragma once

#include "../Window.h"

class VisualInterface {
public:
	VisualInterface() {}

	std::optional<Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	bool close() const noexcept;

private:
	Window window{};
	// TODO: Renderer renderer{};
	
	bool close_request{};
};
