#pragma once

#include <string>
#include "engine/Engine.h"

#undef ERROR

class Editor {
public:
	Editor() {}

	std::optional<Error> init(const std::string& project_path) noexcept;
	void run() noexcept;

private:
	std::string project_path{};
	Engine engine{};
};

