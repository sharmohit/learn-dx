#include "Transform.h"

Transform::Transform()
{
	printf("\nTransform Constructor");
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_scale = { 1.0f, 1.0f, 1.0f };
}

Transform::~Transform()
{
	printf("\nTransform Destructor");
}

void Transform::SetPosition(XMFLOAT3 position)
{
	m_position = position;
}

void Transform::SetRotation(XMFLOAT3 rotation)
{
	m_rotation = rotation;
}

void Transform::SetScale(XMFLOAT3 scale)
{
	m_scale = scale;
}