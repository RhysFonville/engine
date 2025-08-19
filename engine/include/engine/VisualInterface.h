#pragma once

#include "Window.h"
#include "engine/util/debug.h"

class ENGINE_API VisualInterface {
public:
	static std::expected<VisualInterface, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	bool close() const noexcept;

	Window window;
	// TODO: Renderer renderer{};
	
private:
	VisualInterface(Window&& w) : window{std::move(w)} {}

	bool close_request{};
};
