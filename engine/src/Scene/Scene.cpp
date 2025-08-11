#include "engine/Scene/Scene.h"

void Scene::init() noexcept {
	for (Object& obj : objects) {
		obj.init();
	}
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

