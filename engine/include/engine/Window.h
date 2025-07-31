#pragma once

#include <string>
#include <optional>

#include "util/debug.h"

class ENGINE_API Window {
public:
	Window() noexcept;

	std::optional<Error> init() noexcept;
	bool process_events() noexcept;

private:
	struct Impl;
	Impl* impl{nullptr};
};