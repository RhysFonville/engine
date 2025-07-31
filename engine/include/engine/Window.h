#pragma once

#include <string>
#include <memory>
#include <expected>

#include "util/debug.h"

CREATE_ERROR_CATEGORY(window, {
	{1, "Could not create window"}
})

ENGINE_API class Window {
public:
	virtual std::optional<Error> init() const noexcept = 0;
	virtual bool process_events() const noexcept = 0;
};