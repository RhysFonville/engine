#include "UI/EditorUI.h"
#include "Editor.h"

std::expected<Editor, Error> Editor::init(const std::string& project_path) noexcept {
	auto engine{Engine::init(project_path)};
	if (!engine.has_value()) return std::unexpected{engine.error()};
	
	Editor editor{std::move(*engine)};

	editor.project_path = project_path;

	EditorUI::init(engine.value().visuals.window);

	return editor;
}

void Editor::run() noexcept {
	engine.run();
}
