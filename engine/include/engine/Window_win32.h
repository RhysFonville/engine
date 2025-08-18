#pragma once

#include "engine/util/debug.h"

#ifdef RENDERER_D3D12

#include <Windows.h>
#include <optional>

struct WindowImpl {
	std::optional<Error> init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) noexcept;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	HWND hwnd{nullptr};
	WNDCLASSA wc{};
    HINSTANCE hinstance{nullptr};
};

#endif

