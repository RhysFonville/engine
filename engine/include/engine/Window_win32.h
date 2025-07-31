#pragma once

#include <Windows.h>
#include "Window.h"

ENGINE_API class Window_win32 : Window {
public:
	std::optional<void, Error> init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	std::optional<void, Error> init();

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
