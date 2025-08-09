#pragma once

#include <vector>
#include "Object.h"

class Scene {
public:
	Scene() {}
	
	void init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

private:
	std::vector<Object> objects{};
};

