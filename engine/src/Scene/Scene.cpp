#include <ranges>
#include "engine/Scene/Scene.h"

std::expected<Scene, Error> Scene::init() noexcept {
	return Scene{};
}

void Scene::tick() noexcept {
	for (auto& obj : objects) {
		obj.second->tick();
	}
}

void Scene::clean_up() noexcept {
	for (auto& obj : objects) {
		obj.second->clean_up();
	}
}

std::vector<Object*> Scene::get_objects() const noexcept {
	return objects | std::views::values | std::views::transform([](const auto& o) {
		return o.get();
	}) | std::ranges::to<std::vector>();
}

