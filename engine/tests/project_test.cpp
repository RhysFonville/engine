#include <engine/Engine.h>
#include <filesystem>
#include <fstream>
#include <stdio.h>

int main() {
	std::filesystem::create_directory(std::filesystem::current_path() / "test_files/project");

	std::ofstream world_of{"test_files/project/world.json"};
	if (!world_of.is_open()) {
		log(LogLevel::Fatal, "Could not open world.json.");
	}
	world_of <<
		"{"
			"\"scenes\": ["
				"\"scene.json\""
			"],"
			"\"active_scene\": \"scene.json\""
		"}"
	;
	world_of.close();
	if (world_of.is_open()) {
		log(LogLevel::Fatal, "Could not close world.json.");
	}
	std::ofstream scene_of{"test_files/project/scene.json"};
	if (!scene_of.is_open()) {
		log(LogLevel::Fatal, "Could not open scene.json.");
	}
	scene_of <<
		"{"
			"\"objects\": ["
				"{"
					"\"type\": \"Object\""
				"}"
			"]"
		"}"
	;
	scene_of.close();
	if (scene_of.is_open()) {
		log(LogLevel::Fatal, "Could not close scene.json.");
	}

	auto engine{Engine::init((std::filesystem::current_path() / "test_files/project").string())};
	if (!engine.has_value()) {
		log(LogLevel::Fatal, engine.error());
		return EXIT_FAILURE;
	}
	
	if (engine->world.get_scenes().size() != 1) {
		log(LogLevel::Fatal, "Incorrect number of scenes.");
	}
	if (engine->world.get_active_scene() != engine->world.get_scenes()[0]) {
		log(LogLevel::Fatal, "Active scene not set to first in world even though world.json specifies it should be.");
		return EXIT_FAILURE;
	}

	std::filesystem::remove_all("project");

	return EXIT_SUCCESS;
}

