#pragma once

#include <string>

class Object {
public:
	Object() {}

	void init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

private:
	std::string name{};
};

