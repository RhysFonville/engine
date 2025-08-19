#pragma once

#include "engine/util/defines.h"

class ENGINE_API Component {
public:
	void tick() noexcept;
	void clean_up() noexcept;

private:
	Component() {}
};

