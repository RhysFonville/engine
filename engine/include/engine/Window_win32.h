#pragma once

#include <Windows.h>
#include "Window.h"

class ENGINE_API Window_win32 : public Window {
public:
	std::optional<Error> init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	std::optional<Error> init();
	
	virtual void process_events() const noexcept = 0;

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND hwnd{nullptr};
	WNDCLASSA wc{};
};
