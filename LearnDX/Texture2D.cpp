#include <memory>

#include "dxstdafx.h"
#include "Texture2D.h"
#include "WICTextureLoader.h"

Texture2D::Texture2D(std::shared_ptr<DeviceResources> deviceResources, int width, int height) : m_DeviceResources(deviceResources)
{
	m_Width = width;
	m_Height = height; 
}

Texture2D::~Texture2D()
{
}

void Texture2D::CreateTexture()
{
	/*
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = m_Width;
	desc.Height = m_Height;
	desc.MipLevels = 0;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = 0;
	initData.SysMemPitch = static_cast<UINT>(rowPitch);
	initData.SysMemSlicePitch = static_cast<UINT>(imageSize);

	m_DeviceResources->GetDevice()->CreateTexture2D(&desc, &initData, &m_pTexture2D);
	*/
}