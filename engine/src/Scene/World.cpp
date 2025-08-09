#include "engine/Scene/World.h"

void World::init() noexcept {

}

void World::tick() noexcept {
	if (active_scene.has_value())
		active_scene.value()->get()->tick();
}

void World::clean_up() noexcept {
	if (active_scene.has_value())
		active_scene.value()->get()->tick();
}

void World::activate_scene(size_t i) noexcept {
	if (active_scene.has_value())
		active_scene.value()->get()->clean_up();

	active_scene = scenes.begin()+i;
	active_scene.value()->get()->init();
}

void World::add_scene(const std::shared_ptr<Scene>& scene, bool activate) noexcept {
	scenes.emplace_back(scene);
	if (activate) activate_scene(scenes.size()-1);
}

