#pragma once

#include <string>
#include <memory>
#include <optional>

#include "util/debug.h"

class ENGINE_API Window {
public:
	virtual std::optional<Error> init() const noexcept = 0;
	virtual void process_events() const noexcept = 0;
};