#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "LightClass.h"
#include "CameraClass.h"

namespace UI {

		class ImGuiClass
		{

		private:

			bool isAmbientLightOn = true;
			bool isTextureOn = false;
			bool isNormalMapOn = false;

			DirectX::XMFLOAT3 modelPosition;


			DirectX::XMFLOAT3 cameraPoistion;
			DirectX::XMFLOAT3 cameraRotation;
			static void HelpMarker(const char* desc);


		public:
			ImGuiClass();
			~ImGuiClass() = default;

			void Initialize(HWND hwnd, ID3D11Device*, ID3D11DeviceContext*);
			bool GetIsAmbientLightOn();
			bool GetIsTextureOn();
			bool GetIsNormalMapOn();
			DirectX::XMFLOAT3 GetModelPosition();
			void Shutdown();
			void Render(Camera::CameraClass* other);
			LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


		};

	}



