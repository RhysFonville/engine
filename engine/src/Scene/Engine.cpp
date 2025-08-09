#include "engine/Scene/Engine.h"

std::optional<Error> Engine::init() noexcept {
	world.init();
	return visuals.init();
}

void Engine::tick() noexcept {
	world.tick();
	visuals.tick();

	if (visuals.close()) running = false;
}

void Engine::clean_up() noexcept {
	world.clean_up();
	visuals.clean_up();

	running = false;
}

void Engine::run() noexcept {
	while (running) {
		tick();
	}
	clean_up();
}

bool Engine::is_running() const noexcept {
	return running;
}

