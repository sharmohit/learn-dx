#include <memory>

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

	size_t destSize = 4096;
	size_t bytesRead = 0;
	bytes = new BYTE[destSize];

	fopen_s(&vShader, "CubeVertexShader.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 4096, vShader);
	hr = device->CreateVertexShader(
		bytes,
		bytesRead,
		nullptr,
		&m_pVertexShader
		);

	D3D11_INPUT_ELEMENT_DESC iaDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(
		iaDesc,
		ARRAYSIZE(iaDesc),
		bytes,
		bytesRead,
		&m_pInputLayout
		);

	delete bytes;


	bytes = new BYTE[destSize];
	bytesRead = 0;
	fopen_s(&pShader, "CubePixelShader.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 4096, pShader);
	hr = device->CreatePixelShader(
		bytes,
		bytesRead,
		nullptr,
		m_pPixelShader.GetAddressOf()
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
}