#include "Editor.h"

std::optional<Error> Editor::init(const std::string& project_path) noexcept {
	this->project_path = project_path;
	return engine.init();
}

void Editor::run() noexcept {
	engine.run();
}

