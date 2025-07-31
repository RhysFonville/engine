#pragma once

#include <Windows.h>
#include "Window.h"

struct ENGINE_API WindowImpl {
	std::optional<Error> init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) noexcept;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	HWND hwnd{nullptr};
	WNDCLASSA wc{};
};
