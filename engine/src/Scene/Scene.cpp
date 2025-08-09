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

