#pragma once

#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

//#include <Windows.h>
#include "D3dClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorsShaderClass.h"

#include "TextureShaderClass.h"

//GRAPHIC Settings//////

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLE = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;
////////////////////////


class ApplicationClass
{
private:

	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	//ColorsShaderClass* m_ColorShader;

	TextureShaderClass* m_TextureShader;

	bool Render();
	

public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass& other);
	~ApplicationClass();

	bool Initialize(int screenWidth, int screenHight, HWND hwnd);
	void Shutdown();
	bool Frame();





};

#endif 