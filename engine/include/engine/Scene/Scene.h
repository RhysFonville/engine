#pragma once

#include <vector>
#include "Object.h"

class Scene {
public:
	Scene() {}
	
	void init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	const std::vector<Object>& get_objects() const noexcept { return objects; }

private:
	std::vector<Object> objects{};
};

