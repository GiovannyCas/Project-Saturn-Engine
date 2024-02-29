#pragma once

#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

//#include <Windows.h>
#include "D3dClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorsShaderClass.h"

#include "TextureShaderClass.h"

#include "LightShaderClass.h"
#include "LightClass.h"

#include "fontshaderclass.h"
#include "fontclass.h"
#include "textclass.h"


#include "FpsClass.h"


//GRAPHIC Settings//////

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
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

	//TextureShaderClass* m_TextureShader;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	FontShaderClass* m_FontShader;
	FontClass* m_Font;
	

	FpsClass* m_Fps;
	TextClass* m_FpsString;
	int m_previousFps;

	bool Render(float);
	bool UpdateFps();
	

public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass& other);
	~ApplicationClass();

	bool Initialize(int screenWidth, int screenHight, HWND hwnd);
	void Shutdown();
	bool Frame();





};

#endif 