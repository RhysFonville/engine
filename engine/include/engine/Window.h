#pragma once

#include <optional>

#include "util/debug.h"
#include "util/vector.h"

class Window {
public:
	Window() noexcept;
	~Window();
    
    std::optional<Error> clean_up() noexcept;

	std::optional<Error> init() noexcept;
    bool process_events() noexcept;

	const void* get_window_handle() const noexcept;
    void minimize() const noexcept;
    void restore() const noexcept;

    void maximize() const noexcept;

    void hide() const noexcept;
    void show() const noexcept;

    void focus() const noexcept;

    void request_attention() const noexcept;

    void set_title(const std::string& title) const noexcept;
    void set_title(const char* title) const noexcept;

    Vector2 get_position() const noexcept;
    void set_position(const Vector2& position) const noexcept;

    Vector2 get_size() const noexcept;
    void set_size(const Vector2& size) const noexcept;

    void set_size_limits(const Vector2& min, const Vector2& max) const noexcept;

    float get_opacity() const noexcept;
    void set_opacity(float opacity) const noexcept;

    void send_to_front() const noexcept;

private:
    struct Impl;
	std::unique_ptr<Impl> impl{};
};

