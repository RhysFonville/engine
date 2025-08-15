#pragma once

#include <string>
#include "engine/Engine.h"

#undef ERROR

class Editor {
public:

	static std::expected<Editor, Error> init(const std::string& project_path) noexcept;
	void run() noexcept;

private:
	Editor(Engine &&e) : engine{std::move(e)} {}

	std::string project_path;
	Engine engine;
};

