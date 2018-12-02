//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved


//-----------------------------------------------------------------------------
// File: Cube.cpp
//
// Renders a spinning, colorful cube.
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "dxstdafx.h"

#include <string>
#include <memory>
#include <ppltasks.h>

#include "Renderer.h"


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
:
m_frameCount(0),
m_deviceResources(deviceResources)
{
	m_frameCount = 0; // init frame count
}

//-----------------------------------------------------------------------------
// Create Direct3D shader resources by loading the .cso files.
//-----------------------------------------------------------------------------
HRESULT Renderer::CreateShaders()
{
	HRESULT hr = S_OK;
	m_pShader = std::shared_ptr<Shader>(new Shader(m_deviceResources));
	ID3D11Device* device = m_deviceResources->GetDevice();

	CD3D11_BUFFER_DESC cbDesc(
		sizeof(ConstantBufferStruct),
		D3D11_BIND_CONSTANT_BUFFER
		);

	hr = device->CreateBuffer(
		&cbDesc,
		nullptr,
		m_pConstantBuffer.GetAddressOf()
		);


	// Load the extended shaders with lighting calculations.
	/*
	bytes = new BYTE[destSize];
	bytesRead = 0;
	fopen_s(&vShader, "CubeVertexShaderLighting.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 4096, vShader);
	hr = device->CreateVertexShader(
	bytes,
	bytesRead,
	nullptr,
	&m_pVertexShader
	);

	D3D11_INPUT_ELEMENT_DESC iaDescExtended[] =
	{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
	0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,
	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(
	iaDesc,
	ARRAYSIZE(iaDesc),
	bytes,
	bytesRead,
	&m_pInputLayoutExtended
	);

	delete bytes;


	bytes = new BYTE[destSize];
	bytesRead = 0;
	fopen_s(&pShader, "CubePixelShaderPhongLighting.cso", "rb");
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


	bytes = new BYTE[destSize];
	bytesRead = 0;
	fopen_s(&pShader, "CubePixelShaderTexelLighting.cso", "rb");
	bytesRead = fread_s(bytes, destSize, 1, 4096, pShader);
	hr = device->CreatePixelShader(
	bytes,
	bytesRead,
	nullptr,
	m_pPixelShader.GetAddressOf()
	);

	delete bytes;

	fclose(pShader);
	*/

	return hr;
}

//-----------------------------------------------------------------------------
// Create the cube:
// Creates the vertex buffer and index buffer.
//-----------------------------------------------------------------------------
HRESULT Renderer::CreateCube()
{
	HRESULT hr = S_OK;

	m_pModel = std::shared_ptr<Model>(new Model(m_deviceResources));

	return hr;
}

//-----------------------------------------------------------------------------
// Create the view matrix and create the perspective matrix.
//-----------------------------------------------------------------------------
void Renderer::CreateViewAndPerspective()
{
	// Use DirectXMath to create view and perspective matrices.

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.7f, 1.5f, 0.f);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, -0.1f, 0.0f, 0.f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

	DirectX::XMStoreFloat4x4(
		&m_constantBufferData.view,
		DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtRH(
		eye,
		at,
		up
		)
		)
		);

	float aspectRatio = m_deviceResources->GetAspectRatio();

	DirectX::XMStoreFloat4x4(
		&m_constantBufferData.projection,
		DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovRH(
		DirectX::XMConvertToRadians(60),
		aspectRatio,
		0.01f,
		100.0f
		)
		)
		);
}

//-----------------------------------------------------------------------------
// Create device-dependent resources for rendering.
//-----------------------------------------------------------------------------
void Renderer::CreateDeviceDependentResources()
{
	// Compile shaders using the Effects library.
	auto CreateShadersTask = Concurrency::create_task(
		[this]()
	{
		CreateShaders();
	}
	);

	// Load the geometry for the spinning cube.
	auto CreateCubeTask = CreateShadersTask.then(
		[this]()
	{
		CreateCube();
	}
	);
}

void Renderer::CreateWindowSizeDependentResources()
{
	// Create the view matrix and the perspective matrix.
	CreateViewAndPerspective();
}


//-----------------------------------------------------------------------------
// Update the scene.
//-----------------------------------------------------------------------------
void Renderer::Update()
{
	// Rotate the cube 1 degree per frame.
	DirectX::XMStoreFloat4x4(
		&m_constantBufferData.world,
		DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationY(
		DirectX::XMConvertToRadians(
		(float)m_frameCount++
		)
		)
		)
		);

	if (m_frameCount == 400000)  m_frameCount = 0;
}

//-----------------------------------------------------------------------------
// Render the cube.
//-----------------------------------------------------------------------------
void Renderer::Render()
{
	// Use the Direct3D device context to draw.
	ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

	ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTarget();
	ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencil();

	context->UpdateSubresource(
		m_pConstantBuffer.Get(),
		0,
		nullptr,
		&m_constantBufferData,
		0,
		0
		);

	// Clear the render target and the z-buffer.
	//const float teal[] = { 0.192f, 0.301f, 0.474f, 1.000f };
	const float teal[] = { 0.0f, 0.0f, 0.0f, 1.000f };
	context->ClearRenderTargetView(
		renderTarget,
		teal
		);
	context->ClearDepthStencilView(
		depthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Set the render target.
	context->OMSetRenderTargets(
		1,
		&renderTarget,
		depthStencil
		);

	context->VSSetConstantBuffers(
		0,
		1,
		m_pConstantBuffer.GetAddressOf()
		);

	// Calling Draw tells Direct3D to start sending commands to the graphics device.
	context->DrawIndexed(
		m_pModel->GetIndexCount(),
		0,
		0
		);
}

//-----------------------------------------------------------------------------
// Clean up cube resources when the Direct3D device is lost or destroyed.
//-----------------------------------------------------------------------------
Renderer::~Renderer()
{
	// ComPtr will clean up references for us. But be careful to release
	// references to anything you don't need whenever you call Flush or Trim.
	// As always, clean up your system (CPU) memory resources before exit.
}