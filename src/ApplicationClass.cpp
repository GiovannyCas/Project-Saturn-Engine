#include "../src/header/ApplicationClass.h"





ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Input = 0;
	m_Scene = 0;
	m_Timer = 0;
	m_gui = 0;

}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{

	bool result;

	// Create the input object.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the Direct3D object.
	m_Direct3D = new D3DClass;

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Creating the UI object.
	m_gui = new ImGuiClass;

	m_gui->Initialize(hwnd, m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());


	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}


	// Create the zone object.
	m_Scene = new SceneClass;
	if (!m_Scene)
	{
		return false;
	}

	// Initialize the zone object.
	result = m_Scene->Initialize(m_Direct3D, hwnd, screenWidth, screenHeight, SCREEN_DEPTH);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the zone object.", L"Error", MB_OK);
		return false;
	}
	


	return true;
}


void ApplicationClass::Shutdown()
{
	


	// Release the light shader object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	

	// ShutDown the Gui object.
	if (m_gui)
	{
		m_gui->Shutdown();
		delete m_gui;
		m_gui = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	
	// Release the zone object.
	if (m_Scene)
	{
		m_Scene->Shutdown();
		delete m_Scene;
		m_Scene = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}




	return;
}


bool ApplicationClass::Frame()
{
	static float rotation = 0.0f;
	bool result;

	
	m_Timer->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}


	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the zone frame processing.
	result = m_Scene->Frame(m_Direct3D, m_Input, m_ShaderManager, m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	//// Update the rotation variable each frame.
	//rotation -= 0.0174532925f * 0.25f;
	//if (rotation < 0.0f)
	//{
	//	rotation += 360.0f;
	//}

	//// Render the graphics scene.
	//result = Render(rotation);
	//if (!result)
	//{
	//	return false;
	//}

	return true;
}






