#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateMesh(VertexData* meshData)
{
	m_meshData = meshData;
}

VertexData* Mesh::GetMeshData()
{
	return m_meshData;
}

void Mesh::RenderMesh()
{

}