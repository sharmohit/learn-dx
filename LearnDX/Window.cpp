#include "Window.h"

const std::wstring WIN_CLASS_NAME = L"WindowClass";

Window::Window(HINSTANCE hInstance, std::wstring title, int width, int height)
{
	m_hInstance = hInstance;
	m_winTitle = title;
	m_width = width;
	m_height = height;
}

Window::~Window()
{
	UnregisterClass(WIN_CLASS_NAME.c_str(), m_hInstance);
	DestroyWindow(m_hWnd);
}

HRESULT Window::CreateDesktopWindow()
{
	if (m_hInstance == NULL)
		m_hInstance = (HINSTANCE)GetModuleHandle(NULL);

	HICON hIcon = NULL;
	WCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);

	// If the icon is NULL, then use the first one found in the exe
	if (hIcon == NULL)
		hIcon = ExtractIcon(m_hInstance, szExePath, 0);

	// Register the windows class
	WNDCLASS wndClass;
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = Window::StaticWindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = hIcon;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = WIN_CLASS_NAME.c_str();

	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			return HRESULT_FROM_WIN32(dwError);
	}

	m_rc;
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;

	// No menu in this example.
	m_hMenu = NULL;

	SetRect(&m_rc, 0, 0, m_width, m_height);
	AdjustWindowRect(
		&m_rc,
		WS_OVERLAPPEDWINDOW,
		(m_hMenu != NULL) ? true : false
		);

	// Create the window for our viewport.
	m_hWnd = CreateWindow(
		WIN_CLASS_NAME.c_str(),
		m_winTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		x, y,
		(m_rc.right - m_rc.left), (m_rc.bottom - m_rc.top),
		0,
		m_hMenu,
		m_hInstance,
		0
		);

	if (m_hWnd == NULL)
	{
		DWORD dwError = GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}

	return S_OK;
}

LRESULT CALLBACK Window::StaticWindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
					 HMENU hMenu;
					 hMenu = GetMenu(hWnd);
					 if (hMenu != NULL)
					 {
						 DestroyMenu(hMenu);
					 }
					 DestroyWindow(hWnd);
					 UnregisterClass(
						 WIN_CLASS_NAME.c_str(),
						 m_hInstance
						 );
					 return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}