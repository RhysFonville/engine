#include "engine/Window_apple.h"

#ifdef RENDERER_VULKAN

#include <ranges>
#include <algorithm>
#include "engine/Input/InputSet.h"
#include "engine/Window.h"

struct Window::Impl : public WindowImpl { };

static std::optional<Error> glfw_error{std::nullopt};
static std::optional<Error> consume_glfw_error() noexcept {
	auto temp_glfw_error{glfw_error};
	glfw_error = std::nullopt;
	return temp_glfw_error;
}

static std::map<Key, bool> keys_hold{
    std::views::zip(
        std::views::iota(0, (int)Key::KEYS_END-1)
        | std::views::transform([](auto k){ return (Key)k; }),
        std::views::repeat(false, (size_t)Key::KEYS_END)
    ) | std::ranges::to<std::map<Key, bool>>()
};

void WindowImpl::error_callback(int error, const char* description) noexcept {
	glfw_error = Error{std::error_code{error, glfw_category()}};
}

void WindowImpl::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
    if (action == GLFW_PRESS) {
        keys_hold[apple_to_key[scancode]] = true;
    } else if (action == GLFW_RELEASE) {
        keys_hold[apple_to_key[scancode]] = false;
    }

	for (Keybind kb : InputSet::global_keybinds) {
		if (key_to_apple.find(kb.key)->second == scancode &&
            kb.event != KeyEvent::CurrentlyDown &&
            event_to_glfw[kb.event] == action) {
			kb.execute();
        }
	}
}

Window::Window() noexcept : impl{new Impl} { }

std::optional<Error> Window::init() noexcept {
	if (!glfwInit()) return Error{std::error_code{1, glfw_category()}};

	glfwSetErrorCallback(impl->error_callback);
	
	impl->window = glfwCreateWindow(640, 480, "Engine window", NULL, NULL);
	if (auto err{consume_glfw_error()}) return err.value();

	glfwSetKeyCallback(impl->window, impl->key_callback);

	return std::nullopt;
}

std::optional<Error> Window::clean_up() noexcept {
	glfwTerminate();
	glfwDestroyWindow(impl->window);
	return std::nullopt;
}

bool Window::process_events() noexcept {
	glfwPollEvents();
    
    for (auto kb : InputSet::global_keybinds) {
        if (kb.event == KeyEvent::CurrentlyDown) {
            if (keys_hold[kb.key]) {
                kb.execute();
            }
        }
    }

	return !glfwWindowShouldClose(impl->window);
}

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

#endif

