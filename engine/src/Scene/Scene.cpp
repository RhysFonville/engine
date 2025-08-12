#include "engine/Scene/Scene.h"

std::expected<Scene, Error> Scene::init() noexcept {
	return Scene{};
}

void Scene::tick() noexcept {
	for (Object& obj : objects) {
		obj.tick();
	}
}

void Scene::clean_up() noexcept {
	for (Object& obj : objects) {
		obj.clean_up();
	}
}

void Scene::add_object(const Object& object) noexcept {
	objects.emplace_back(object);
}

