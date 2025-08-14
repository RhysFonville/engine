#pragma once

class Component {
public:
	void tick() noexcept;
	void clean_up() noexcept;

private:
	Component() {}
};

