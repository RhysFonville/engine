#pragma once

#include "Scene/World.h"
#include "VisualInterface.h"

class Engine {
public:
	Engine() {}

	std::optional<Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	void run() noexcept;
	bool is_running() const noexcept;

	World world{};
	VisualInterface visuals{};

private:
	bool running{true};
};

