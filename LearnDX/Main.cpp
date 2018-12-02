//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved


//-----------------------------------------------------------------------------
// File: Main.cpp
//
// Desktop app that renders a spinning, colorful cube.
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "dxstdafx.h"

#include <string>
#include <memory>

#include "DeviceResources.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Window.h"

int main()
{
	WinMain(GetModuleHandle(NULL), NULL, NULL, 0);
}

//-----------------------------------------------------------------------------
// Main function: Creates window, calls initialization functions, and hosts
// the render loop.
//-----------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HRESULT hr = S_OK;

	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Begin initialization.

	// Instantiate the window manager class.
	std::shared_ptr<Window> window = std::shared_ptr<Window>(new Window(hInstance, L"LearnDX", 960, 480));

	// Create a window.
	hr = window->CreateDesktopWindow();

	if (SUCCEEDED(hr))
	{
		// Instantiate the device manager class.
		std::shared_ptr<DeviceResources> deviceResources = std::shared_ptr<DeviceResources>(new DeviceResources());
		// Create device resources.
		deviceResources->CreateDeviceResources();

		// Instantiate the renderer.
		std::shared_ptr<Renderer> renderer = std::shared_ptr<Renderer>(new Renderer(deviceResources));
		renderer->CreateDeviceDependentResources();

		// We have a window, so initialize window size-dependent resources.
		deviceResources->CreateWindowResources(window->GetWindowHandle());
		renderer->CreateWindowSizeDependentResources();

		// Go full-screen.
		//deviceResources->GoFullScreen();

		// Whoops! We resized the "window" when we went full-screen. Better
		// tell the renderer.
		renderer->CreateWindowSizeDependentResources();

		// Run the program.
		if (!IsWindowVisible(window->GetWindowHandle()))
			ShowWindow(window->GetWindowHandle(), SW_SHOW);

		// Initialize SceneManager.
		std::shared_ptr<SceneManager> sceneManager = std::shared_ptr<SceneManager>(new SceneManager());
		sceneManager->LoadScene(Main_Scene);

		// The render loop is controlled here.
		bool bGotMsg;
		MSG  msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

		while (WM_QUIT != msg.message)
		{
			// Process window events.
			// Use PeekMessage() so we can use idle time to render the scene. 
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Update the scene.
				sceneManager->Update(0);
				renderer->Update();

				// Render frames during idle time (when no messages are waiting).
				sceneManager->Render();
				renderer->Render();

				// Present the frame to the screen.
				deviceResources->Present();
			}
		}
		sceneManager->Quit();
	}

	// Cleanup is handled in destructors.
	return hr;
}