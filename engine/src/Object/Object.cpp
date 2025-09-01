#include "engine/Object/Object.h"

BEGIN_DEFS(Object)

std::expected<Object, Error> Object::init() noexcept {
	auto reg_obj{RegistrationObject::init()};
	if (!reg_obj.has_value()) return std::unexpected{reg_obj.error()};
	Object obj{std::move(*reg_obj)};

#define MK_PROPERTY(var) std::string{typeid(var).name()}, #var, (void*)&var
	obj.properties.emplace_back(MK_PROPERTY(obj.id));
	obj.properties.emplace_back(MK_PROPERTY(obj.components));
#undef MK_PROPERTY

	return obj;
}

void Object::tick() noexcept {

}

void Object::clean_up() noexcept {

}

void Object::set_property_from_json(const Property& prop, const nlohmann::json& value) {
	
}
