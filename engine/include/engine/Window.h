#pragma once

#include <optional>
#include <expected>

#include "util/debug.h"

CREATE_ERROR_CATEGORY(window, {
    {1, "Could not initialize glfw."},
    {2, "Could not create window.h"}
})

class ENGINE_API Window {
public:
	Window() noexcept;
    
    void clean_up() noexcept;

	std::optional<Error> init() noexcept;
    std::expected<bool, Error> process_events() noexcept;

private:
    struct Impl;
	Impl* impl{nullptr};
};
