#pragma once

#include "D3dClass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "timerclass.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "SkydomeClass.h"
#include "TerrainClass.h"


class SceneClass
{
private:
	CameraClass* m_Camera;
	PositionClass* m_Position;
	SkyDomeClass* m_SkyDome;
	TerrainClass* m_Terrain;
	
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*);
	

public:
	SceneClass();

	bool Initialize(D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, float);



};

