#include "project/MyObject.h"

std::expected<MyObject, Error> MyObject::init() noexcept {
	auto obj{Object::init()};
	if (!obj.has_value()) return std::unexpected{obj.error()};
	return MyObject{std::move(*obj)};
}
