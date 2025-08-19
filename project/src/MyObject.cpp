#include "project/MyObject.h"

std::expected<MyObject, Error> MyObject::init() noexcept {
	return MyObject{};
}
