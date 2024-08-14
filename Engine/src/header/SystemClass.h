#pragma once


#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "InputClass.h"
#include "ApplicationClass.h"
#include "TimerClass.h"




class SystemClass
{
private:

	
	LPCWSTR		 m_applicationName;
	HINSTANCE	 m_hinstance;
	HWND		 m_hwnd;

	ApplicationClass*	m_Application;


	
	
	
	bool Frame();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();
	
public:
	

	SystemClass();
	~SystemClass() = default;

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	
};


static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = 0;


