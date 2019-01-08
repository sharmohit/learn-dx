#include <memory>
#include<comdef.h>

#include "dxstdafx.h"
#include "Shader.h"

Shader::Shader(std::shared_ptr<DeviceResources> deviceResources) : m_deviceResources(deviceResources)
{
	CreateShader();
}

Shader::~Shader()
{
}

void Shader::CreateShader()
{
	HRESULT hr = S_OK;

	// Use the Direct3D device to load resources into graphics memory.
	ID3D11Device* device = m_deviceResources->GetDevice();

	ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

	// You'll need to use a file loader to load the shader bytecode. In this
	// example, we just use the standard library.
	FILE* vShader, *pShader;
	BYTE* bytes;

	size_t destSize = 20480;
	size_t bytesRead = 0;
	bytes = new BYTE[destSize];

	fopen_s(&vShader, "VertexShaderTex.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 20480, vShader);
	hr = device->CreateVertexShader(
		bytes,
		bytesRead,
		nullptr,
		&m_pVertexShader
		);

	if (FAILED(hr))
	{
		_com_error err(hr);
		LPCTSTR errMsg = err.ErrorMessage();
		printf("ERR:%s\n", errMsg);
	}

	D3D11_INPUT_ELEMENT_DESC iaDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3D11_INPUT_ELEMENT_DESC iaAdvanceDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(
		iaAdvanceDesc,
		ARRAYSIZE(iaAdvanceDesc),
		bytes,
		bytesRead,
		&m_pInputLayout
		);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, &m_pSamplerState);

	delete bytes;


	bytes = new BYTE[destSize];
	bytesRead = 0;
	fopen_s(&pShader, "PixelShaderTex.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 20480, pShader);
	hr = device->CreatePixelShader(
		bytes,
		bytesRead,
		nullptr,
		&m_pPixelShader
		);

	delete bytes;

	fclose(vShader);
	fclose(pShader);

	// Set the IA Stage 
	context->IASetInputLayout(m_pInputLayout.Get());

	// Set up the vertex shader stage.
	context->VSSetShader(
		m_pVertexShader.Get(),
		nullptr,
		0
		);

	// Set up the pixel shader stage.
	context->PSSetShader(
		m_pPixelShader.Get(),
		nullptr,
		0
		);

	context->PSSetSamplers(0, 1, &m_pSamplerState);

}

void Shader::Render()
{
	// Set up the vertex shader stage.
	m_deviceResources->GetDeviceContext()->VSSetShader(
		m_pVertexShader.Get(),
		nullptr,
		0
		);

	// Set up the pixel shader stage.
	m_deviceResources->GetDeviceContext()->PSSetShader(
		m_pPixelShader.Get(),
		nullptr,
		0
		);
	m_deviceResources->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);
}