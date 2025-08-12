#pragma once

#include <vector>
#include "Object.h"

class Scene {
public:
	static std::expected<Scene, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	const std::vector<Object>& get_objects() const noexcept { return objects; }
	void add_object(const Object& object) noexcept;

private:
	Scene() {}

	std::vector<Object> objects{};
};

