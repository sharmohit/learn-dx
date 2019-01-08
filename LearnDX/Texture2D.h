#pragma once

#include "DeviceResources.h"

class Texture2D
{
public:
	Texture2D(std::shared_ptr<DeviceResources> deviceResources,
		int width, int height);
	~Texture2D();
private:
	void CreateTexture();

	std::shared_ptr<DeviceResources> m_DeviceResources;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D;
	int m_Width;
	int m_Height;
};