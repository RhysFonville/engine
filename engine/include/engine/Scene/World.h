#pragma once

#include <vector>
#include "Scene.h"
#include "engine/util/debug.h"

CREATE_ERROR_CATEGORY(world, {
	{1, "Index of scene to activate out of bounds"},
	{2, "Nullptr passed when adding new scene"}
})

class World {
public:
	static std::expected<World, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	std::optional<Error> activate_scene(size_t i) noexcept;
	std::optional<Error> add_scene(const std::shared_ptr<Scene>& scene, bool activate = true) noexcept;

	const std::vector<std::shared_ptr<Scene>>& get_scenes() const noexcept { return scenes; }
	const std::shared_ptr<Scene>& get_active_scene() const noexcept { return scenes[active_scene]; }

private:
	World() : active_scene{scenes.size()} {}

	std::vector<std::shared_ptr<Scene>> scenes{};
	size_t active_scene{};
};

