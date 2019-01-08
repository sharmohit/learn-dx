#pragma once

class DeviceResources
{
public:
	DeviceResources();
	~DeviceResources();

	HRESULT CreateDeviceResources();
	HRESULT CreateWindowResources(HWND hWnd);

	HRESULT ConfigureBackBuffer();
	HRESULT ConfigureDepthStencilState();
	HRESULT ConfigureRasterizerState();
	HRESULT ReleaseBackBuffer();
	HRESULT GoFullScreen();
	HRESULT GoWindowed();

	float GetAspectRatio();

	ID3D11Device*           GetDevice() { return m_pd3dDevice.Get(); };
	ID3D11DeviceContext*    GetDeviceContext() { return m_pd3dDeviceContext.Get(); };
	ID3D11RenderTargetView* GetRenderTarget() { return m_pRenderTarget.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView() { return m_pDepthStencilView.Get(); }
	ID3D11DepthStencilState* GetDepthStencilState() { return m_pDepthStencilState.Get(); }
	ID3D11RasterizerState* GetRasterizerState() { return m_pRasterizerState.Get(); }

	void Present();

private:

	//-----------------------------------------------------------------------------
	// Direct3D device
	//-----------------------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Device>        m_pd3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>      m_pDXGISwapChain;


	//-----------------------------------------------------------------------------
	// DXGI swap chain device resources
	//-----------------------------------------------------------------------------
	Microsoft::WRL::ComPtr < ID3D11Texture2D>        m_pBackBuffer;
	Microsoft::WRL::ComPtr < ID3D11RenderTargetView> m_pRenderTarget;


	//-----------------------------------------------------------------------------
	// Direct3D device resources for the depth stencil
	//-----------------------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_pDepthStencil;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>  m_pDepthStencilState;


	//-----------------------------------------------------------------------------
	// Direct3D device resources for the Rasterizer State
	//-----------------------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>         m_pRasterizerState;


	//-----------------------------------------------------------------------------
	// Direct3D device metadata and device resource metadata
	//-----------------------------------------------------------------------------
	D3D_FEATURE_LEVEL       m_featureLevel;
	D3D11_TEXTURE2D_DESC    m_bbDesc;
	D3D11_VIEWPORT          m_viewport;
};