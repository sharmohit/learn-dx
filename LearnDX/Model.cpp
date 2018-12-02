#include <memory>

#include "dxstdafx.h"
#include "Model.h"

Model::Model(std::shared_ptr<DeviceResources> deviceResources) : m_deviceResources(deviceResources)
{
	CreateModel();
}

Model::~Model()
{
}

void Model::CreateModel()
{
	HRESULT hr = S_OK;

	// Use the Direct3D device to load resources into graphics memory.
	ID3D11Device* device = m_deviceResources->GetDevice();

	ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

	// Create cube geometry.
	VertexPositionColor CubeVertices[] =
	{
		{ DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(0, 0, 0), },
		{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(0, 0, 1), },
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, -0.5f), DirectX::XMFLOAT3(0, 1, 0), },
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0, 1, 1), },

		{ DirectX::XMFLOAT3(0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(1, 0, 0), },
		{ DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(1, 0, 1), },
		{ DirectX::XMFLOAT3(0.5f, 0.5f, -0.5f), DirectX::XMFLOAT3(1, 1, 0), },
		{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1, 1, 1), },
	};

	// Create vertex buffer:

	CD3D11_BUFFER_DESC vDesc(
		sizeof(CubeVertices),
		D3D11_BIND_VERTEX_BUFFER
		);

	D3D11_SUBRESOURCE_DATA vData;
	ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
	vData.pSysMem = CubeVertices;
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(
		&vDesc,
		&vData,
		&m_pVertexBuffer
		);

	// Create index buffer:
	unsigned short CubeIndices[] =
	{
		0, 2, 1, // -x
		1, 2, 3,

		4, 5, 6, // +x
		5, 7, 6,

		0, 1, 5, // -y
		0, 5, 4,

		2, 6, 7, // +y
		2, 7, 3,

		0, 4, 6, // -z
		0, 6, 2,

		1, 3, 7, // +z
		1, 7, 5,
	};

	m_indexCount = ARRAYSIZE(CubeIndices);

	CD3D11_BUFFER_DESC iDesc(
		sizeof(CubeIndices),
		D3D11_BIND_INDEX_BUFFER
		);

	D3D11_SUBRESOURCE_DATA iData;
	ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
	iData.pSysMem = CubeIndices;
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(
		&iDesc,
		&iData,
		&m_pIndexBuffer
		);

	// Set up the IA stage by setting the input topology and layout.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		m_pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_pIndexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0
		);

	context->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
}