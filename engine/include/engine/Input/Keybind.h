#pragma once

#include <functional>
#include "Key.h"

class Keybind {
public:
    Keybind(Key key, KeyEvent event, const std::function<void()>& callback)
        : key{key}, event{event}, callback{callback} { }

    void execute() const { callback(); }

    Key key{};
    KeyEvent event{};
    std::function<void()> callback{};
};

