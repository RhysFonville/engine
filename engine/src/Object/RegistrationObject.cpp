#include "engine/Object/RegistrationObject.h"

RegistrationObject::RegistrationObject(RegistrationObject&&) noexcept = default;
RegistrationObject& RegistrationObject::operator=(RegistrationObject&&) noexcept = default;
RegistrationObject::RegistrationObject() noexcept : name{}, properties{} { }
RegistrationObject::~RegistrationObject() = default;

std::expected<RegistrationObject, Error> RegistrationObject::init() noexcept {
	return RegistrationObject{};
}

