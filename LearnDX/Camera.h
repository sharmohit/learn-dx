/*
#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9math.h>

class Camera
{
public:
	Camera();
	~Camera();

	D3DXVECTOR3 GetPosition() const { return position; }
	D3DXVECTOR3 GetRotation() const { return rotation; }

	void SetPosition(D3DXVECTOR3 position) { this->position = position; }
	void SetRotation(D3DXVECTOR3 rotation) { this->rotation = rotation; }
	void Render();

private:
	D3DXVECTOR3 up;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;

	D3DXMATRIX rotationMatrix;
	D3DXMATRIX viewMatrix;
};

#endif
*/