#pragma once

#include <string>

class Object {
public:
	Object() {}

	bool operator==(const Object& obj) const noexcept { return name == obj.name; }

	void init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	std::string name{};
};

