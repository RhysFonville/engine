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

std::expected<Object*, Error> Scene::add_object() noexcept {
	ObjectID id = object_id_counter++;

	auto obj{Object::init()};
	if (!obj.has_value()) return std::unexpected{obj.error()};

	auto ent{objects.insert({id, std::make_unique<Object>(std::move(obj.value()))})};
	return ent.first->second.get();
}

std::vector<Object*> Scene::get_objects() const noexcept {
	return objects | std::views::values | std::views::transform([](const auto& o) {
		return o.get();
	}) | std::ranges::to<std::vector>();
}

