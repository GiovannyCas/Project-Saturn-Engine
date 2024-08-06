#pragma once

#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_



#include <DirectXMath.h>





class CameraClass
{
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	DirectX::XMMATRIX m_viewMatrix, m_baseViewMatrix;

public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(DirectX::XMMATRIX&);

	void RenderBaseViewMatrix();
	void GetBaseViewMatrix(DirectX::XMMATRIX&);





};

#endif 