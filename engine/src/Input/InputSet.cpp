#include "engine/Input/InputSet.h"

std::vector<Keybind> InputSet::global_keybinds = {};

void InputSet::set_keybinds(const std::vector<Keybind>& keybinds) noexcept {
    if (global_keybinds.empty()) {
        global_keybinds = keybinds;
        global_keybinds_it = global_keybinds.begin();
        return;
    }
    
    global_keybinds.erase(global_keybinds_it, global_keybinds_it+this->keybinds.size());

    global_keybinds_it = global_keybinds.cend();
    global_keybinds.insert(global_keybinds.end(), keybinds.begin(), keybinds.end());
}

