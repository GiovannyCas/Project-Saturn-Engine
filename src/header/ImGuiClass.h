#pragma once

#ifndef _IMGUICLASS_H_
#define _IMGUICLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include "LightClass.h"
#include "CameraClass.h"

class ImGuiClass
{

private:
	
	
	DirectX::XMFLOAT4 col2;
	DirectX::XMFLOAT3 Dirc;

public:
	ImGuiClass();
	ImGuiClass(ImGuiClass& other);
	~ImGuiClass();

	void Initialize(HWND hwnd, ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(CameraClass* other);
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	
};
#endif

