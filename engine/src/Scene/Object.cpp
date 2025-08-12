#include "engine/Scene/Object.h"

std::expected<Object, Error> Object::init() noexcept {
	return Object{};
}

void Object::tick() noexcept {

}

void Object::clean_up() noexcept {

}

