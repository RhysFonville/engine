#pragma once

#include "engine/util/defines.h"

#ifdef RENDERER_VULKAN

#include <GLFW/glfw3.h>
#include "engine/util/debug.h"

struct ENGINE_API WindowImpl {
    static void error_callback(int error, const char* description) noexcept;
    std::optional<Error> error{std::nullopt};

    GLFWwindow* window{nullptr};
};

#endif

