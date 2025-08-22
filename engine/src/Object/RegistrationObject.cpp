#include "engine/Object/RegistrationObject.h"

std::expected<RegistrationObject, Error> RegistrationObject::init() noexcept {
	return RegistrationObject{};
}

