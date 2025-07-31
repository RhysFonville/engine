#include "engine/Window_apple.h"

#ifdef RENDERER_VULKAN

#include "engine/Window.h"

struct ENGINE_API Window::Impl : public WindowImpl { };

Window::Window() noexcept : impl{new Impl} { }

std::optional<Error> Window::init() noexcept {
    if (!glfwInit()) return Error{std::error_code{1, window_category()}};

    glfwSetErrorCallback(impl->error_callback);
    
    impl->window = glfwCreateWindow(640, 480, "Engine window", NULL, NULL);
    if (!impl->window) return Error{std::error_code{2, window_category()}};

    return std::nullopt;
}

void Window::clean_up() noexcept {
    glfwTerminate();
    glfwDestroyWindow(impl->window);
}

void WindowImpl::error_callback(int error, const char* description) noexcept {
    
}

std::expected<bool, Error> Window::process_events() noexcept {
    if (impl->error.has_value()) return std::unexpected{impl->error.value()};

    glfwPollEvents();

    return !glfwWindowShouldClose(impl->window);
}

#endif

