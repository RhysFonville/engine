#include "engine/Object/Object.h"

BEGIN_DEFS(Object)

std::expected<Object, Error> Object::init() noexcept {
	return Object{};
}

void Object::tick() noexcept {

}

void Object::clean_up() noexcept {

}

const std::vector<Property>& Object::get_properties() const {
	return static_properties();
}

void Object::set_property_from_json(const Property& prop, const nlohmann::json& value) {
	
}
