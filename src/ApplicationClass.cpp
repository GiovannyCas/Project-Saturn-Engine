#include "../src/header/ApplicationClass.h"





ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Light = 0;
	m_gui = 0;
	m_Position = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

	char fpsString[32];
	char modelFilename[128];
	char textureFilename[128];
	char NormalMapFilename[128];
	bool result;


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

	// Create the camera object.
	m_Camera = new CameraClass;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_Position = new PositionClass;

	if (!m_Position)
	{
		return false;
	}

	m_Position->SetPosition(0.0f, 0.0f, -10.0f);

	// Set the file name of the model.
	strcpy_s(modelFilename, "resources/cube.txt");

	// Set the file name of the texture file that we will be loading.
	strcpy_s(textureFilename, "resources/stone01.tga");
	strcpy_s(NormalMapFilename, "resources/normal01.tga");

	// Create and initialize the model object.
	m_Model = new ModelClass;

	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename, NormalMapFilename);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// Create and initialize the light object.
	m_Light = new LightClass;

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	//Create and initialize the shader manger object.
	m_ShaderManager = new ShaderManagerClass;

	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}


	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}


	// Release the light shader object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// ShutDown the Gui object.
	if (m_gui)
	{
		m_gui->Shutdown();
		delete m_gui;
		m_gui = 0;
	}

	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}




	return;
}


bool ApplicationClass::Frame()
{
	static float rotation = 0.0f;
	bool result;


	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * 0.25f;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool ApplicationClass::Render(float rotation)
{
	DirectX::XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	rotateMatrix = DirectX::XMMatrixRotationY(rotation);  // Build the rotation matrix.
	translateMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);  // Build the translation matrix.

	// Rotate the world matrix by the rotation value so that the model will spin.
	worldMatrix = DirectX::XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	
	m_Model->Render(m_Direct3D->GetDeviceContext());
	
	if (m_gui->GetIsTextureOn())
	{
		// Render the model using the Texture shader.
		result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0));
		if (!result)
		{
			return false;
		}
	}


	if (m_gui->GetIsAmbientLightOn()) {
		// Render the model using the light shader.
		
		result = m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
	}

	if (m_gui->GetIsNormalMapOn())
	{
		
		// Render the model using the Normal Map shader.
		result = m_ShaderManager->RenderNormalMapShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model->GetTexture(0), m_Model->GetTexture(1), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
	}

	// Disable the Z buffer and enable alpha blending for 2D rendering.
	/*m_Direct3D->TurnZBufferOff();
	m_Direct3D->EnableAlphaBlending();*/

	//m_Direct3D->GetWorldMatrix(worldMatrix);

	// Enable the Z buffer and disable alpha blending now that 2D rendering is complete.
	/*m_Direct3D->TurnZBufferOn();
	m_Direct3D->DisableAlphaBlending();*/

	m_gui->Render(m_Camera);

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}



bool ApplicationClass::HandleInput(float frameTime, int input)
{

	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	switch (input)
	{
	case 1:
		m_Position->MoveDownward(true);
		break;
	case 2:
		m_Position->LookDownward(true);
		break;
	case 3:
		m_Position->MoveUpward(true);
		break;
	case 4:
		m_Position->LookUpward(true);
		break;
	case 5:
		m_Position->MoveForward(true);
		break;
	case 6:
		m_Position->TurnLeft(true);
		break;
	case 7:
		m_Position->MoveBackward(true);
		break;
	case 8:
		m_Position->TurnRight(true);
		break;
	default:
		break;
	}


	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}