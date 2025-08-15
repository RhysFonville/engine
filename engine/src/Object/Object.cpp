#include "engine/Object/Object.h"

std::expected<Object, Error> Object::init() noexcept {
	return Object{};
}

void Object::tick() noexcept {

}

void Object::clean_up() noexcept {

}

const std::vector<Property>& Object::get_properties() const {
	return {
		Property{"ObjectID", "id", (void*)&id},
		Property{"std::vector<Component*>", "components", (void*)&components}
	};
}

void Object::set_property_from_json(const Property& prop, const nlohmann::json& value) {
	
}
