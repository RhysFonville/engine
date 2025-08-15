#pragma once

#include <vector>
#include "Scene.h"
#include "engine/util/debug.h"
#include "engine/AssetManager/AssetManager.h"

CREATE_ERROR_CATEGORY(world, {
	{1, "Index of scene to activate out of bounds"},
	{2, "Nullptr passed when adding new scene"},
	{3, "Active scene value when reading scene file does not match up with any added scene"},
	{4, "Invalid file (does not exist/is not regular/does not have json extension"},
	{5, "Could not open file"},
	{6, "Could not close file"},
	{7, "Could not parse json"},
})

class World {
public:
	static std::expected<World, Error> init() noexcept;
	static std::expected<World, Error> init(AssetManager& asset_manager, const std::string& world_file) noexcept;
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

