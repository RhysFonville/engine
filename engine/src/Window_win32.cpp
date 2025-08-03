#include "engine/Window_win32.h"

#ifdef RENDERER_D3D12

#include "engine/Window.h"

struct Window::Impl : public WindowImpl { };

static std::optional<std::pair<Vector2, Vector2>> set_size_limit{std::nullopt};

Window::Window() noexcept : impl{new Impl} { }

std::optional<Error> WindowImpl::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) noexcept {
    hinstance = hInstance;

	constexpr const char CLASS_NAME[]{"Window"};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	
	if (!RegisterClassA(&wc))
		return Error{std::error_code{(int)GetLastError(), std::system_category()}};

	// Create the window
	hwnd = CreateWindowExA(
		0ul,                       // Optional window styles.
		CLASS_NAME,                     // Window class
		"Engine Window",                // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,                           // Parent window    
		NULL,                           // Menu
		hInstance,                      // Instance handle
		NULL                            // Additional application data
	);

	if (hwnd == NULL)
		return Error{std::error_code{(int)GetLastError(), std::system_category()}};

	ShowWindow(hwnd, nCmdShow);

	return std::nullopt;
}

std::optional<Error> Window::init() noexcept {
	return impl->init(GetModuleHandleA(NULL), NULL, LPSTR(""), 0);
}

std::optional<Error> Window::clean_up() noexcept {
    if (!DestroyWindow(impl->hwnd))
		return Error{std::error_code{(int)GetLastError(), std::system_category()}};

	if (!UnregisterClassA(impl->wc.lpszClassName, impl->hinstance))
		return Error{std::error_code{(int)GetLastError(), std::system_category()}};

	return std::nullopt;
}

bool Window::process_events() noexcept {
	MSG msg{};
	while (PeekMessageA(&msg, impl->hwnd,  0u, 0u, PM_REMOVE))  {
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	return true;
}

LRESULT CALLBACK WindowImpl::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept {
	switch (uMsg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		case WM_GETMINMAXINFO: {
			if (set_size_limit.has_value()) {
				MINMAXINFO* mmi = (MINMAXINFO*)lParam;
				mmi->ptMinTrackSize.x = set_size_limit->first.x;
				mmi->ptMinTrackSize.y = set_size_limit->first.y;
				mmi->ptMaxTrackSize.x = set_size_limit->second.x;
				mmi->ptMaxTrackSize.y = set_size_limit->second.y;
			}
		}
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

void Window::minimize() const noexcept {
	ShowWindow(impl->hwnd, SW_MINIMIZE);
}

void Window::restore() const noexcept {
	ShowWindow(impl->hwnd, SW_RESTORE);
}

void Window::maximize() const noexcept {
	ShowWindow(impl->hwnd, SW_MAXIMIZE);
}

void Window::hide() const noexcept {
	ShowWindow(impl->hwnd, SW_HIDE);
}
void Window::show() const noexcept {
	ShowWindow(impl->hwnd, SW_SHOW);
}

void Window::focus() const noexcept {
	SetFocus(impl->hwnd);
}

void Window::request_attention() const noexcept {
	static FLASHWINFO info{
		.cbSize = sizeof(FLASHWINFO),
		.hwnd = impl->hwnd,
		.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG,
		.uCount = NULL,
		.dwTimeout = NULL
	};
	FlashWindowEx(&info);
}

void Window::set_title(const std::string& title) const noexcept {
	set_title(title.c_str());
}

void Window::set_title(const char* title) const noexcept {
	SetWindowTextA(impl->hwnd, title);
}

Vector2 Window::get_position() const noexcept {
	RECT rect{};
	GetWindowRect(impl->hwnd, &rect);
	return Vector2{rect.left, rect.top};
}

void Window::set_position(const Vector2& position) const noexcept {
	SetWindowPos(impl->hwnd, NULL, position.x, position.y, NULL, NULL, SWP_NOSIZE);
}

Vector2 Window::get_size() const noexcept {
	RECT rect{};
	GetWindowRect(impl->hwnd, &rect);
	return Vector2{rect.right-rect.left, rect.bottom - rect.top};
}

void Window::set_size(const Vector2& size) const noexcept {
	SetWindowPos(impl->hwnd, NULL, NULL, NULL, size.x, size.y, SWP_NOMOVE);
}

void Window::set_size_limits(const Vector2& min, const Vector2& max) const noexcept {
	set_size_limit = std::make_pair(min, max);
}

float Window::get_opacity() const noexcept {
	BYTE alpha{};
	DWORD flags{};
	if (GetLayeredWindowAttributes(impl->hwnd, NULL, &alpha, &flags)) {
		if (flags & LWA_ALPHA) {
			return (float)alpha / 255.f;
		}
	}
	return .0f;
}

void Window::set_opacity(float opacity) const noexcept {
	SetWindowLongPtrA(impl->hwnd, GWL_EXSTYLE, GetWindowLongPtrA(impl->hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(impl->hwnd, NULL, BYTE(255.f*opacity), LWA_ALPHA);
}

void Window::send_to_front() const noexcept {
	BringWindowToTop(impl->hwnd);
}

#endif
