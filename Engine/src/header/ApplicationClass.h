#pragma once

#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

//#include <Windows.h>
#include "D3dClass.h"
#include "TimerClass.h"
#include "ShaderManagerClass.h"
#include "SceneClass.h"
#include "InputClass.h"
#include "ImGuiClass.h"





//GRAPHIC Settings//////

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
////////////////////////

enum groupLabel : std::size_t
{
	groupMap,
	groupPlayer,
	groupUI,
	groupEnemy
};

class ApplicationClass
{
private:

	DX::DirectXClass* m_Direct3D;
	Shader::ShaderManagerClass* m_ShaderManager;
	Utility::SceneClass* m_Scene;
	Utility::TimerClass* m_Timer;
	Input::InputClass* m_Input;
	UI::ImGuiClass* m_gui;
	

public:
	ApplicationClass();
	~ApplicationClass() = default;

	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame();





};

#endif 