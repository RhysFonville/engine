#include "engine/Scene/World.h"

void World::init() noexcept {
	if (active_scene != scenes.size())
		get_active_scene()->init();
}

void World::tick() noexcept {
	if (active_scene != scenes.size())
		get_active_scene()->tick();
}

void World::clean_up() noexcept {
	if (active_scene != scenes.size())
		get_active_scene()->tick();
}

std::optional<Error> World::activate_scene(size_t i) noexcept {
	if (i >= scenes.size()) return Error{1, world_category()};

	if (active_scene != scenes.size())
		get_active_scene()->clean_up();

	active_scene = i;
	get_active_scene()->init();

	return std::nullopt;
}

std::optional<Error> World::add_scene(const std::shared_ptr<Scene>& scene, bool activate) noexcept {
	if (scene == nullptr) return Error{2, world_category()};

	if (active_scene == scenes.size())
		active_scene++;

	scenes.emplace_back(scene);

	if (activate) activate_scene(scenes.size()-1);

	return std::nullopt;
}

