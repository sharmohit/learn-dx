#pragma once

#include <string>
#include <Windows.h>

class Window {
public:
	Window(HINSTANCE hInstance, std::wstring title, int width, int height);
	~Window();

	HRESULT CreateDesktopWindow();
	HWND GetWindowHandle() { return m_hWnd; };

	static LRESULT CALLBACK StaticWindowProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);

private:
	HMENU          m_hMenu;
	RECT           m_rc;
	HWND           m_hWnd;
	std::wstring   m_winTitle;
	int            m_width;
	int            m_height;
};

static HINSTANCE m_hInstance;