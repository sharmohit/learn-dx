#pragma once

#include "DeviceResources.h"
#include "Model.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<DeviceResources> deviceResources);
	~Renderer();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();
	void Update();
	void Render();

private:
	HRESULT CreateShaders();
	HRESULT CreateCube();
	void    CreateViewAndPerspective();

	//-----------------------------------------------------------------------------
	// Pointer to device resource manager
	//-----------------------------------------------------------------------------
	std::shared_ptr<DeviceResources> m_deviceResources;

	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Shader> m_pShader;


	typedef struct _constantBufferStruct {
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	} ConstantBufferStruct;

	// Assert that the constant buffer remains 16-byte aligned.
	static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

	//-----------------------------------------------------------------------------
	// Per-vertex data (extended)
	//-----------------------------------------------------------------------------
	typedef struct _vertexPositionColorTangent
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT3 tangent;
	} VertexPositionColorTangent;

	ConstantBufferStruct m_constantBufferData;
	unsigned int  m_frameCount;

	//-----------------------------------------------------------------------------
	// Direct3D device resources
	//-----------------------------------------------------------------------------
	//ID3DXEffect* m_pEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_pInputLayoutExtended;
	Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pConstantBuffer;
};