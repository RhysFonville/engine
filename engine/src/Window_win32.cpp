#include "engine/Window_win32.h"

#ifdef RENDERER_D3D12

std::optional<Error> Window_win32::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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

std::optional<Error> Window_win32::init() {
	return init(GetModuleHandleA(NULL), NULL, LPSTR(""), 0);
}

void Window_win32::process_events() const noexcept {
	MSG msg{};
	while (PeekMessageA(&msg, hwnd,  0u, 0u, PM_REMOVE)) 
	{ 
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	} 
}

LRESULT CALLBACK Window_win32::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
