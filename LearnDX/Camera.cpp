/*
#include"Camera.h"

Camera::Camera()
{
	position.x = 30.0;
	position.y = -20.0;
	position.z = 0.0;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
}

Camera::~Camera()
{
}

void Camera::Render()
{
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 0.0, 0.0, 0.0);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt = position + lookAt;

	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
}
*/