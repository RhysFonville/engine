#include "UI/EditorUI.h"
#include "Editor.h"

std::optional<Error> Editor::init(const std::string& project_path) noexcept {
	this->project_path = project_path;

	auto res{engine.init()};
	EditorUI::init(engine.visuals.window);

	return res;
}

void Editor::run() noexcept {
	engine.run();
}

