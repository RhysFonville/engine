#include <fstream>
#include <filesystem>
#include "engine/Scene/World.h"

std::expected<World, Error> World::init() noexcept {
	return World{};
}

std::expected<World, Error> World::init(AssetManager& asset_manager, const std::string& world_file) noexcept {
	World world{};

	std::filesystem::path path{world_file};
	if (!std::filesystem::exists(path) ||
		!std::filesystem::is_regular_file(path) ||
		path.extension() != ".json") return std::unexpected{Error{4, world_category()}};
	
	std::ifstream in{world_file};
	if (!in.is_open()) return std::unexpected{Error{5, world_category()}};

	nlohmann::json json{nlohmann::json::parse(in)};

	in.close();
	if (in.is_open()) return std::unexpected{Error{5, world_category()}};

	std::vector<std::string> scene_files{};
	for (auto& scene_file_json : json["scenes"]) {
		std::string scene_file{scene_file_json.get<std::string>()};
		scene_files.emplace_back(scene_file);

		auto scene_res{asset_manager.load<Scene>(scene_file)};
		if (!scene_res.has_value()) return std::unexpected{scene_res.error()};

		std::shared_ptr<Scene> scene{scene_res.value()};
		world.add_scene(scene, false);
	}

	auto it{std::ranges::find(scene_files, json["active_scene"].get<std::string>())};
	if (it != scene_files.end()) {
		world.active_scene = std::distance(scene_files.begin(), it);
		if (auto res{world.activate_scene(world.active_scene)}; res.has_value())
			return std::unexpected{res.value()};
	} else {
		return std::unexpected{Error{3, world_category()}};
	}

	return world;
}

void World::tick() noexcept {
	if (active_scene != scenes.size())
		get_active_scene()->tick();
}

void World::clean_up() noexcept {
	if (active_scene != scenes.size())
		get_active_scene()->tick();
}

std::optional<Error> World::activate_scene(size_t i) noexcept {
	if (i >= scenes.size()) return Error{1, world_category()};

	if (active_scene != scenes.size())
		get_active_scene()->clean_up();

	active_scene = i;
	if (auto res{get_active_scene()->init()}; !res.has_value()) return res.error();

	return std::nullopt;
}

std::optional<Error> World::add_scene(const std::shared_ptr<Scene>& scene, bool activate) noexcept {
	if (scene == nullptr) return Error{2, world_category()};

	if (active_scene == scenes.size())
		active_scene++;

	scenes.emplace_back(scene);

	if (activate) activate_scene(scenes.size()-1);

	return std::nullopt;
}

