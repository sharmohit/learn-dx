#include "dxstdafx.h"

#include <string>
#include <memory>

#include "DeviceResources.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Window.h"
#include "WICTextureLoader.h"

int main()
{
	WinMain(GetModuleHandle(NULL), NULL, NULL, 0);
}


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

	std::shared_ptr<Window> window = std::shared_ptr<Window>(new Window());
	hr = window->CreateDesktopWindow(hInstance, L"LearnDX", 1920, 1080);

	if (SUCCEEDED(hr))
	{
		std::shared_ptr<DeviceResources> deviceResources = std::shared_ptr<DeviceResources>(new DeviceResources());
		deviceResources->CreateDeviceResources();

		std::shared_ptr<Renderer> renderer = std::shared_ptr<Renderer>(new Renderer(deviceResources));
		renderer->CreateDeviceDependentResources();

		// We have a window, so initialize window size-dependent resources.
		deviceResources->CreateWindowResources(window->GetWindowHandle());
		renderer->CreateWindowSizeDependentResources();

		//deviceResources->GoFullScreen();

		// Whoops! We resized the "window" when we went full-screen. Better
		// tell the renderer.
		renderer->CreateWindowSizeDependentResources();

		// Run the program.
		if (!IsWindowVisible(window->GetWindowHandle()))
			ShowWindow(window->GetWindowHandle(), SW_SHOW);

		std::shared_ptr<SceneManager> sceneManager = std::shared_ptr<SceneManager>(new SceneManager());
		sceneManager->LoadScene(Main_Scene);

		ID3D11Resource* textureResource;
		ID3D11ShaderResourceView* shaderResourceView;
		hr = CreateWICTextureFromFile(deviceResources->GetDevice(),
			deviceResources->GetDeviceContext(),
			L"tex_pyramid.jpg",
			&textureResource,
			&shaderResourceView);

		if (FAILED(hr))
		{
			printf("\nTexture Failed");
		}
		else
		{
			printf("\nTexture Success");
		}
		deviceResources->GetDeviceContext()->PSSetShaderResources(0, 1, &shaderResourceView);

		bool bGotMsg;
		MSG  msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

		while (WM_QUIT != msg.message)
		{ 
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				sceneManager->Update(0);
				renderer->Update();

				sceneManager->Render();
				renderer->Render();

				deviceResources->Present();
			}
		}
		sceneManager->Quit();
	}

	return hr;
}