#pragma once

#include <string>
#include "../util/debug.h"

class Object {
public:
	bool operator==(const Object& obj) const noexcept { return name == obj.name; }

	static std::expected<Object, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	std::string name{};

private:
	Object() {}
};

