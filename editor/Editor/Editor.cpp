#include <sstream>
#include "UI/EditorUI.h"
#include "Editor.h"

std::expected<Editor, Error> Editor::init(const std::string& project_path) noexcept {
	auto engine{Engine::init(project_path)};
	if (!engine.has_value()) return std::unexpected{engine.error()};
	
	Editor editor{std::move(*engine)};

	editor.project_path = project_path;

	EditorUI::init(engine.value().visuals.window);

	for (const auto& scene : editor.engine.world.get_scenes()) {
		log("Scene 1:");
		for (const auto& obj : scene->get_objects()) {
			log("\t" + obj->get_registered_name() + ":");
			for (const auto& property : obj->get_properties()) {
				const void* address = static_cast<const void*>(property.pointer);
				std::stringstream ss{};
				ss << address;
				log("\t\t&" + property.type + " " + property.name + " = " + ss.str());
			}
		}
	}

	return editor;
}

void Editor::run() noexcept {
	engine.run();
}
