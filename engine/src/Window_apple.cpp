#include "engine/Window_apple.h"

#ifdef RENDERER_VULKAN

#include "engine/Window.h"

struct ENGINE_API Window::Impl : public WindowImpl { };

Window::Window() noexcept : impl{new Impl} { }

static std::optional<Error> glfw_error{std::nullopt};
static std::optional<Error> consume_glfw_error() noexcept {
    auto temp_glfw_error{glfw_error};
    glfw_error = std::nullopt;
    return temp_glfw_error;
}

std::optional<Error> Window::init() noexcept {
    if (!glfwInit()) return Error{std::error_code{1, glfw_category()}};

    glfwSetErrorCallback(impl->error_callback);
    
    impl->window = glfwCreateWindow(640, 480, "Engine window", NULL, NULL);
    if (auto err{consume_glfw_error()}) return err.value();

    return std::nullopt;
}

void Window::clean_up() noexcept {
    glfwTerminate();
    glfwDestroyWindow(impl->window);
}

void WindowImpl::error_callback(int error, const char* description) noexcept {
    glfw_error = Error{std::error_code{error, glfw_category()}};
}

bool Window::process_events() noexcept {
    glfwPollEvents();
    return !glfwWindowShouldClose(impl->window);
}

#endif

void Window::minimize() const noexcept {
    glfwIconifyWindow(impl->window);
}

void Window::restore() const noexcept {
    glfwRestoreWindow(impl->window);
}

void Window::maximize() const noexcept {
    glfwMaximizeWindow(impl->window);
}

void Window::hide() const noexcept {
    glfwHideWindow(impl->window);
}

void Window::show() const noexcept {
    glfwShowWindow(impl->window);
}

void Window::focus() const noexcept {
    glfwFocusWindow(impl->window);
}

void Window::request_attention() const noexcept {
    glfwRequestWindowAttention(impl->window);
}

void Window::set_title(const std::string& title) const noexcept {
    glfwSetWindowTitle(impl->window, title.c_str());
}

void Window::set_title(const char* title) const noexcept {
    glfwSetWindowTitle(impl->window, title);
}

Vector2 Window::get_position() const noexcept {
    Vector2 ret{};
    glfwGetWindowPos(impl->window, &ret.x, &ret.y);
    return ret;
}

void Window::set_position(const Vector2& position) const noexcept {
    glfwSetWindowPos(impl->window, position.x, position.y);
}

Vector2 Window::get_size() const noexcept {
    Vector2 ret{};
    glfwGetWindowSize(impl->window, &ret.x, &ret.y);
    return ret;
}

void Window::set_size(const Vector2& size) const noexcept {
    glfwSetWindowSize(impl->window, size.x, size.y);
}

void Window::set_size_limits(const Vector2& min, const Vector2& max) const noexcept {
    glfwSetWindowSizeLimits(impl->window, min.x, min.y, max.x, max.y);
}

float Window::get_opacity() const noexcept {
    return glfwGetWindowOpacity(impl->window);
}

void Window::set_opacity(float opacity) const noexcept {
    glfwSetWindowOpacity(impl->window, opacity);
}

void Window::send_to_front() const noexcept {
    focus();
}

