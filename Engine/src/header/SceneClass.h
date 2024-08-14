#pragma once

#include "D3dClass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "timerclass.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "SkydomeClass.h"
#include "TerrainClass.h"


	namespace Utility {
		class SceneClass
		{
		private:
			Camera::CameraClass* m_Camera;
			PositionClass* m_Position;
			SkyDomeClass* m_SkyDome;
			TerrainClass* m_Terrain;

			void HandleMovementInput(Input::InputClass*, float);
			bool Render(DX::DirectXClass*, Shader::ShaderManagerClass*);


		public:
			SceneClass();
			~SceneClass() = default;
			bool Initialize(DX::DirectXClass*, HWND, int, int, float);
			void Shutdown();
			bool Frame(DX::DirectXClass*, Input::InputClass*, Shader::ShaderManagerClass*, float);



		};

	}


