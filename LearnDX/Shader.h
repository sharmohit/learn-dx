#pragma once

#include "DeviceResources.h"

class Shader
{
public:
	Shader(std::shared_ptr<DeviceResources> deviceResources);
	~Shader();

	void Render();

private:
	void CreateShader();

	std::shared_ptr<DeviceResources> m_deviceResources;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>      m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       m_pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		m_pSamplerState;
};