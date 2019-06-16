#pragma once

#include <memory>

#include "dxstdafx.h"
using namespace DirectX;

typedef struct m_vertextData{
	XMFLOAT3 position;
}VertexData;

class Mesh {
public:
	Mesh();
	~Mesh();

	void CreateMesh(VertexData* meshData);
	void RenderMesh();
	VertexData* GetMeshData();
private:
	VertexData* m_meshData;
};