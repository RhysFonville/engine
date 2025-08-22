#include "engine/Object/Object.h"
#include "engine/Object/RegistrationObject.h"

BEGIN_DEFS(Object)

std::expected<Object, Error> Object::init() noexcept {
	auto reg_obj{RegistrationObject::init()};
	if (!reg_obj.has_value()) return std::unexpected{reg_obj.error()};
	return Object{std::move(*reg_obj)};
}

void Object::tick() noexcept {

}

void Object::clean_up() noexcept {

}

void Object::set_property_from_json(const Property& prop, const nlohmann::json& value) {
	
}
