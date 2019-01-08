#pragma once

#include "DeviceResources.h"

class Model{
public:
	Model(std::shared_ptr<DeviceResources> deviceResources);
	~Model();

	unsigned int GetIndexCount() { return m_indexCount; };

private:
	void CreateModel();

	std::shared_ptr<DeviceResources> m_deviceResources;

	/*
	typedef struct _vertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	} VertexPositionColor;
	*/

	typedef struct _vertexPositionTexture
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	} VertexPositionTexture;

	unsigned int  m_indexCount;

	Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pIndexBuffer;
};