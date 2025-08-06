#pragma once

#include <vector>
#include "Keybind.h"

class InputSet {
public:
	InputSet() { }

    void set_keybinds(const std::vector<Keybind>& keybinds) noexcept;

private:
    friend class WindowImpl;
    friend class Window;

    static std::vector<Keybind> global_keybinds;

	std::vector<Keybind> keybinds{};
    std::vector<Keybind>::const_iterator global_keybinds_it{};
};

