#include "engine/Window_win32.h"

#ifdef RENDERER_D3D12

#include "engine/Window.h"

struct ENGINE_API Window::Impl : public WindowImpl { };

Window::Window() noexcept : impl{new Impl} { }

std::optional<Error> WindowImpl::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) noexcept {
    hinstance = hInstance;

	constexpr const char CLASS_NAME[]{"Window"};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	
	RegisterClassA(&wc);

	if (auto err{GetLastError()}; err == 0)
		return Error{std::error_code{(int)err, std::system_category()}};

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

	if (hwnd == NULL) {
		return Error{std::error_code{(int)GetLastError(), std::system_category()}};
	}

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
}

std::expected<bool, Error> Window::process_events() noexcept {
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
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// Draw "Hello, World!"
			TextOutA(hdc, 10, 10, "Hello, World!", (int)wcslen(L"Hello, World!"));

			EndPaint(hwnd, &ps);
			return 0;
		}
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

#endif
