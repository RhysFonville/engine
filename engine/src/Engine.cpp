#include "engine/Engine.h"

std::expected<Engine, Error> Engine::init() noexcept {
	auto w{World::init()};
	auto vi{VisualInterface::init()};
	auto am{AssetManager::init()};
	if (!w.has_value()) return std::unexpected{w.error()};
	if (!vi.has_value()) return std::unexpected{vi.error()};
	if (!am.has_value()) return std::unexpected{am.error()};
	return Engine{std::move(*w), std::move(*vi), std::move(*am)};
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

