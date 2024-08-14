#pragma once


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

namespace Input
{

	class InputClass
	{

	private:
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keyboard;
		IDirectInputDevice8* m_mouse;

		unsigned char m_keyboardState[256];
		DIMOUSESTATE m_mouseState;

		int m_screenWidth, m_screenHeight;
		int m_mouseX, m_mouseY;

		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();


	public:
		InputClass();
		~InputClass() = default;

		bool Initialize(HINSTANCE, HWND, int, int);
		void Shutdown();
		bool Frame();

		int HandleInput();

		void GetMouseLocation(int&, int&);

		bool IsEscapePressed();
		bool IsLeftPressed();
		bool IsRightPressed();
		bool IsUpPressed();
		bool IsDownPressed();
		bool IsSPressed();
		bool IsAPressed();
		bool IsWPressed();
		bool IsDPressed();


	};
}


