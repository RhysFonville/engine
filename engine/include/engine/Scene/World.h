#pragma once

#include <vector>
#include <optional>
#include "Scene.h"

class World {
public:
	World() {}

	void init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	void activate_scene(size_t i) noexcept;
	void add_scene(const std::shared_ptr<Scene>& scene, bool activate = true) noexcept;

	const std::vector<std::shared_ptr<Scene>>& get_scenes() const noexcept { return scenes; }

private:
	std::vector<std::shared_ptr<Scene>> scenes{};
	std::optional<std::vector<std::shared_ptr<Scene>>::iterator> active_scene{std::nullopt};
};

