#pragma once

#include "dxstdafx.h"
using namespace DirectX;

class Transform{
public:
	Transform();
	~Transform();

	XMFLOAT3 GetPosition(){ return m_position; }; 
	XMFLOAT3 GetRotation(){ return m_rotation; };
	XMFLOAT3 GetScale(){ return m_scale; };

	void SetPosition(XMFLOAT3 position);
	void SetRotation(XMFLOAT3 rotation);
	void SetScale(XMFLOAT3 scale);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_scale;
};